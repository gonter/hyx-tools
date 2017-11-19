/*
 *  FILE %ned/11/ned1105.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *    ned_str_match: Suchen eines Strings im NED Zeilen Speicher
 *                   und Angabe der Position des gefundenen Strings
 *
 *  written:       1988 09 20
 *                 1989 06 18
 *                 1990 01 21: Revision
 *                 1991 01 31: Revision
 *                 1991 12 31: revision: bracket match
 *  latest update: 1998-08-16 19:21:31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_str_match (
struct LINE *z_start,           /* Start Zeile                              */
int c_start,                    /* Start Spalte                             */
struct LINE *z_end,             /* Ende Zeile                               */
unsigned char *mtch,            /* Match String                             */
unsigned char *ignore,          /* Ignore String (matching brackets)        */
int matching_ignore_level,      /* ev. Verschachtelungsebene                */
struct LINE **z_fnd,            /* Zeile des gefundenen Strings             */
int *c_fnd,                     /* Spalte des gefundenen Strings            */
int *ml,                        /* laenge des gematchten Strings            */
int option)                     /* Find&Replace Optionen                    */
/* RETURN: -1 ...                  Suchanfang undefiniert oder nicht gef.   */
/*          0 ...                  gefunden !!!                             */
{
  int m_char= 0;                /* Zeichen im Match String                  */
  int m_lng= 0;                 /* Laenge des gematchten Strings            */
  int t_char;                   /* Zeichen im Text                          */
  int status= -1;               /* Zustand des Match-Automaten              */
  struct LINE *zz_start;        /* untersuchte Zeile                        */
  struct LINE *zz_save;         /* saved first line                         */
  int          cc_start;        /* untersuchte Spalte                       */
  unsigned char *mp=            /* Match Pointer                            */
    (unsigned char *) 0;
  int ignore_level= -1;         /* number of ignored strings ...            */
                                /* bracket under cursor increments level!   */
  int wrapped= 0;               /* 1 -> started on top once already         */

  if ((zz_start= zz_save= z_start) == (struct LINE *) 0) return -1;
  cc_start= c_start;

  if (z_end != (struct LINE *) 0) wrapped= 1; /* do not allow wrapping! */

  while (1)
    switch (status)
    {
      case -1:
WRAPPED:
        mp= mtch;

        if (*mp == '^')
        { /* ^ at the beginning of the match string means that              */
          /* we are looking for that pattern at beginning of the line       */
          if (c_start > 0) goto MATCH_FAILED;
          mp++;
        }

        m_lng= 0;
        status= 0;

      case 0: /* Zeichen im Match String analysieren */
        if ((m_char= (*mp++ & 0x00FF)) == 0) goto FOUND;
        if (z_start == (struct LINE *) 0)
        {
NOT_FOUND:
          if (!wrapped 
              && (option & OPT_wrapscan)
              && zz_save != (struct LINE *) 0
             )
          { /* T2D: wrapscan does not work yet !! */
            wrapped= 1;

            z_end= zz_save;
            if (option & OPT_backward)
            {
              z_start= ned_find_last_line (zz_save);
              c_start= z_start->lng-1;
            }
            else
            {
              z_start= ned_find_first_line (zz_save);
              c_start= 0;
            }
            status= -1;
            zz_start= z_start;
            cc_start= c_start;

            ned_message_1 ("wrapped ...");
            goto WRAPPED;
          }

          *z_fnd= (struct LINE *) 0;
          *c_fnd= -1;
          *ml= -1;
          return -1;
        }

        switch (m_char)
        {
          case 0: /* Match String am Ende: -> Zeichen gefunden */
FOUND:
            if (ignore_level != matching_ignore_level)
            {
              ignore_level--;
              goto MATCH_FAILED;
            }
            *z_fnd= zz_start;
            *c_fnd= cc_start;
            *ml= m_lng;
            return 0;

#ifdef SONDERBEHANDLUNG
          /* Wildcards usw. werden irgendwann einmal    */
          /* besonders behandelt werden ....            */
          case '*': if (*mp == 0) goto FOUND;
          case '\\':
            status= 1;  /* <<<<<<<<<<<<< vorlauefig */
            break;
          case '?': goto NEXT_CHARACTER;
#endif
          default:
            status= 1;
            goto STATUS1;
        }
        break;

      case 1: /* Zeichen im Text vergleichen */
STATUS1:
        /* T2D: inlining get_txt koennte hier einiges an        */
        /*      Geschwindigkeit rausholen, da das Duchsteppen   */
        /*      des txt Pointers wegfallen wuerde.  1998-08-16  */
        t_char= get_txt (z_start, c_start);

        if (option & OPT_upper)
        { /* Option u (Uppercase): kein Case-Checking */
          if (t_char >= 'A' && t_char <= 'Z') t_char = t_char - 'A' + 'a';
          if (m_char >= 'A' && m_char <= 'Z') m_char = m_char - 'A' + 'a';
        }

        if (ignore != (unsigned char *) 0 && t_char == *ignore)
          ignore_level++;

        if (t_char != m_char)
        { /* auf eine neues; Zeichen passen nicht zusammen */
MATCH_FAILED:
          if (option & OPT_backward)
          {
            if (--cc_start < 0)
            {
              if (z_start == z_end
                  || (zz_start= zz_start->prev) == (struct LINE *) 0
                 ) goto NOT_FOUND;

              cc_start= zz_start->lng -1;
            }
          }
          else
          {
            if (++cc_start >= zz_start->lng)
            {
              if (z_start == z_end
                  || (zz_start= zz_start->next) == (struct LINE *) 0
                 ) goto NOT_FOUND;

              cc_start= 0;
            }
          }

          z_start= zz_start;
          c_start= cc_start;
          status= -1;
        }
        else
        {
          m_lng++;
          status= 0; /* naechstes Zeichen */
          if (option & OPT_backward)
          {
            if (c_start == 0 &&
                (*mp & 0x00FF) == 0)    /* backward search where matchng    */
                goto FOUND;             /* string is at the begin of line   */

            if (--c_start < 0)
            {
              if (*mp) goto MATCH_FAILED;
              if (z_start == z_end
                  || (z_start= z_start->prev) == (struct LINE *) 0
                 ) goto NOT_FOUND;

              c_start= z_start->lng -1;
              status= -1;
            }
          }
          else
          {
            if (++c_start >= z_start->lng)
            { /* at the end of the line, check if match string is at the    */
              /* end too, if not, the match failed unless the remaining     */
              /* match string is just a '$'                                 */

              if (*mp == 0 || (*mp == '$' && mp [1] == 0)) goto FOUND;
              if (*mp) goto MATCH_FAILED;

              if (z_start == z_end
                  || (z_start= z_start->next) == (struct LINE *) 0
                 ) goto NOT_FOUND;

              c_start= 0;
              status= -1;
            }
          }
        }
        break;
    }

  return -1;
}

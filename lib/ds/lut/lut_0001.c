/*
 *  FILE %ds/lut/lut_0001.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbuechern
 *  see also: lookup_file
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1990 05 31: lut_word_match
 *                 1991 03 15: Revision; AIX
 *  latest update: 1995-12-20
 *
 */

/* #define DEBUG_001 */
/* #define DEBUG_002 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
static char lut_word_buffer [MAX_LUT_KEY_LENGTH];
                                        /* Puffer fuer gefundenes Wort      */
static char *lut_dump_beg= (char *) 0;  /* begin of dump window             */
static char *lut_dump_end= (char *) 0;  /* end of dump window               */

/* ------------------------------------------------------------------------ */
int lookup_char (
char *lut,                      /* Look Up Table                            */
const char *w,                  /* string to be found                       */
long *w_info,                   /* -> informationen about the word          */
int *lng)                       /* length of matching word                  */
                                /* important for LOOKUP_prefix              */
/* RETURN: siehe File LOOKUP.H                                              */
{
  int ret_val= 0;               /* return code: bitmapped values            */
  int idx= 0;                   /* untersuchte Stelle im Key (Suchwort)     */
  register char *cp;            /* untersuchte Stelle in der LUT            */
  char *retry_position;         /* resync position for another alternative  */
  long offset_value;            /* value of a offset code for skip entry    */
  char *prev_offset= (char *) 0;/* frame position for alternative key dumps */

  if ((cp= lut) == (char *) 0 || *cp == 0x00) return LOOKUP_empty;
  if (nl_key_valid (w) == -1) return LOOKUP_error;

  retry_position= (char *) 0;

  for (; cp != (char *) 0;)
  {
    switch (*cp)
    {
      case 0x00: /* Wortende; -> Information einmal sicherstellen */
        if (w [idx] == 0)
        { /* gesuchtes Wort gefunden  */
          *w_info= dpp_get_long (&cp[1], 4);
          *lng= idx;
          return ret_val | LOOKUP_found;
        }
        else
        { /* o  hier wurde ein Wort gefunden, welches         */
          /*    auch im gesuchten Wort auftritt               */
          /* o  Da eine lexikalische Sortierung vor-          */
          /*    liegt, muss weiter gesucht werden.            */
          *lng= idx;
          *w_info= dpp_get_long (&cp[1], 4);
          ret_val |= LOOKUP_prefix;
          goto TRY_ANOTHER;
        }
        break;

      default:
        if (*cp != (w [idx] & 0x00FF))
        {
          if (w [idx] == 0)
          {
            if (retry_position != (char *) 0)
            {
              goto LONG2;
            }
            else
            { /* o  w is a prefix for at least one other word               */
              /* -> search can be stopped here                              */
              /* -> it can be found out if just one other word follows      */
              /* -> info codes for more following words can be idetified    */
              for (; cp != (char *) 0; cp++)
                switch (*cp)
                {
                  case 0x00: /* Wortende; */
                    *w_info= dpp_get_long (&cp[1], 4);
                    *lng= idx;
                    return ret_val | LOOKUP_prefix_3;
                  case 0x01:
                  case 0x02:
                  case 0x03:
                  case 0x04:
LONG2:
                    lut_dump_beg= cp; /* back_step??? see lookup_file */
                    lut_dump_end= prev_offset-1;
                    *lng= idx;
                    return ret_val | LOOKUP_prefix_4;
                  default:
                    if (idx+1 < MAX_LUT_KEY_LENGTH)
                    {
                      lut_word_buffer [idx++]= *cp;
                      lut_word_buffer [idx]= 0;
                    }
                    else
                      idx++;
                    break;
                }
              return -4; /* das duerfte nicht auftreten */
            }
          }
TRY_ANOTHER:
          cp= retry_position;
          if (retry_position != (char *) 0) prev_offset= retry_position;
          retry_position= (char *) 0;
        }
        else
        { /* bisheriger Wortteil in LUT */
          if (idx+1 < MAX_LUT_KEY_LENGTH)
          {
            lut_word_buffer [idx++]= *cp;
            lut_word_buffer [idx]= 0;
          }
          else
            idx++;
          cp++;
          if (retry_position != (char *) 0) prev_offset= retry_position;
          retry_position= (char *) 0;
        }
        break;

      /* Offset Codes */
      case  4:
      case  3:
#ifdef MSDOS
        return LOOKUP_error_size;
#endif
      case  2:
      case  1:
        offset_value= dpp_get_long (&cp[1], *cp);
        cp += (*cp)+1;
        retry_position= cp + offset_value;
/**********
printf ("cp=0x%lX offset_value=0x%X retry_position=0x%lX\n",
cp, offset_value, retry_position);
**********/
        break;
    }
  }

  /* Wort nicht gefunden */
  return ret_val;
}

/* ------------------------------------------------------------------------ */
char *lut_char_get_word_buffer ()
{
  return lut_word_buffer;
}

/* ------------------------------------------------------------------------ */
char *lut_char_get_dump_beg ()
{
  return lut_dump_beg;
}

/* ------------------------------------------------------------------------ */
char *lut_char_get_dump_end ()
{
  return lut_dump_end;
}

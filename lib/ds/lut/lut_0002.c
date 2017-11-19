/*
 *  FILE %nl_kr/lib/lut_0002.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbuechern
 *  see also: lookup_char
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *  latest update: 1995-12-03
 *  $Id: lut_0002.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
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
static long lut_dump_beg= -1L;          /* begin of dump window             */
static long lut_dump_end= -1L;          /* end of dump window               */

/* ------------------------------------------------------------------------ */
int lookup_file (
FILE *lut,                      /* Look Up Table; binaer eroeffnet          */
                                /* und ev. an den Anfang positioniert       */
const char *w,                  /* Word                                     */
long *w_info,                   /* -> Informationen ueber Word              */
int  *lng)                      /* Laenge des gematchten Wortes             */
                                /* Wichtig bei LOOKUP_prefix                */
/* RETURN: siehe File LOOKUP.H                                              */
{
  int ret_val= 0;               /* Return Code: bitmapped values            */
  int idx= 0;                   /* untersuchte Stelle im Key (Suchwort)     */
  int cp;                       /* untersuchtes Zeichen aus LUT             */
  long retry_position;          /* resync position for another alternative  */
  long offset_value;            /* value of a offset code for skip entry    */
  long prev_offset= -1L;        /* frame position for alternative key dumps */
  long back_step= 0L;           /* number of bytes to step back             */

  if (nl_key_valid (w) == -1) return LOOKUP_error;

  /* 1. Zeichen einlesen */
  cp= fgetc (lut) & 0x00FF;
  if (feof (lut) || cp == 0x00) return LOOKUP_empty;

  retry_position= -1L;
  for (;;)
  {
    switch (cp)
    {
      case  0: /* Wortende */
        if (w [idx] == 0)
        { /* Wort gefunden */
          lut_dump_beg= (retry_position == -1L)
                        ? -1L : ftell (lut) - back_step;
          *w_info= dpp_fread_long (lut, 4);
          *lng= idx;
          return ret_val | LOOKUP_found;
        }
        else
        { /* hier wurde ein Wort gefunden, welches    */
          /* auch im gesuchten Wort auftritt          */
          *lng= idx;
          *w_info= dpp_fread_long (lut, 4);
          ret_val |= LOOKUP_prefix;
          goto TRY_ANOTHER;
        }
        break;

      default:
        if (cp != (w [idx] & 0x00FF))
        {
         if (w [idx] == 0) /* WHAT???? */
         {
          if (retry_position != -1L)
          {
            lut_dump_beg= ftell (lut) - back_step;
            goto LONG2;
          }
          else
          { /* o  w is a prefix for at least one other word                 */
            /* -> search can be stopped here                                */
            /* -> it can be found out if just one other word follows        */
            /* -> info codes for more following words can be idetified      */
            for (; !feof (lut); cp= fgetc (lut) & 0x00FF)
              switch (cp)
              {
                case 0x00: /* Wortende; */
                  *w_info= dpp_fread_long (lut, 4);
                  *lng= idx;
                  return ret_val | LOOKUP_prefix_3;
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                  lut_dump_beg= ftell (lut) - 1L;
LONG2:
                  lut_dump_end= prev_offset -1L;
                  *lng= idx;
                  return ret_val | LOOKUP_prefix_4;
                default:
                  if (idx+1 < MAX_LUT_KEY_LENGTH)
                  {
                    lut_word_buffer [idx++]= (char) cp;
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
         if (retry_position == -1L) goto NOT_FOUND;
         fseek (lut, retry_position, 0);
        }
        else
        { /* bisheriger Wortteil in LUT */
          if (idx+1 < MAX_LUT_KEY_LENGTH)
          {
            lut_word_buffer [idx++]= (char) cp;
            lut_word_buffer [idx]= 0;
          }
          else
            idx++;
        }
        if (retry_position != -1L) prev_offset= retry_position;
        retry_position= -1L;
        break;

      /* Offset Codes */
      case  1:
      case  2:
      case  3:
      case  4:
        back_step= (long) (2+cp);
        offset_value= dpp_fread_long (lut, cp);
        retry_position= ftell (lut) + offset_value;
/***********
printf ("cp=0x%lX offset_value=0x%X retry_position=0x%lX\n",
cp, offset_value, retry_position);
***********/
        break;
    }

    /* read next character from the LUT */
    cp= fgetc (lut) & 0x00FF;
    if (feof (lut)) break;
  }

NOT_FOUND:
  /* word could not be found ... */
  return ret_val;
}

/* ------------------------------------------------------------------------ */
char *lut_file_get_word_buffer ()
{
  return lut_word_buffer;
}

/* ------------------------------------------------------------------------ */
long lut_file_get_dump_beg ()
{
  return lut_dump_beg;
}

/* ------------------------------------------------------------------------ */
long lut_file_get_dump_end ()
{
  return lut_dump_end;
}

/*
 *  FILE ~/usr/ds/hyxp/hyxp0007.c
 *
 *  read one lexicon entry
 *
 *  written:       1995-03-19
 *  latest update: 1995-08-05
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/diagnose.h>

/* ------------------------------------------------------------------------ */
int hyx_parse2_string (
struct HYX_PARSER_STATUS *hps,  /* currently processed SGML structure       */
char *str,                      /* string to be read                        */
struct TEXT_ELEMENT **le,       /* datastructure to be built                */
long end_tags [],               /* set of possible end tags                 */
int end_tag_count,              /* number of possible endtags               */
long max_to_read,               /* number of bytes to be read at most       */
long *bytes_read)               /* number of bytes actually read            */
{
  int rc= 0;
  int ch;                       /* character read                           */
  long byte_count= 0L;          /* number of bytes read sofar               */

  gg_diagnose= LEX_RT_no_frame_close;

  if (bytes_read == (long *) 0
     || str == (char *) 0
     || hps == (struct HYX_PARSER_STATUS *) 0
     || le == (struct TEXT_ELEMENT **) 0)
  {
    gg_diagnose= LEX_RT_init_error;
    return -1;
  }

  if (max_to_read <= 0L) goto STOP;

  for (;; max_to_read--)
  {
    if (max_to_read > 0L)
    {
      ch= *str++ & 0x00FF;
      if (ch == 0)
      {
        if (byte_count == 0L) break;
        ch= -1;
      }
      else
      {
        byte_count++;
      }
    }
    else ch= -1;

    if ((rc= hyx_parse2_char (hps, le, ch, end_tags, end_tag_count)) != 0)
    {
      if (rc > 0) rc= 0;
      break;
    }
  }

STOP:
  *bytes_read= byte_count;

  return rc;
}

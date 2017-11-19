/*
 *  FILE %ds/hyxp/hyxp0008.c
 *
 *  incrementally parse a block of data a SGML structure
 *
 *  written:       1995-08-05: derived from hyx_parse2_string ()
 *  latest update: 1995-08-05
 *  $Id: hyxp0008.c,v 1.3 2003/06/25 10:11:56 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/diagnose.h>

/* ------------------------------------------------------------------------ */
int hyx_parse2_block (
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
      || le == (struct TEXT_ELEMENT **) 0
     )
  {
    gg_diagnose= LEX_RT_init_error;
    return -1;
  }

  if (max_to_read <= 0L) goto STOP;

  for (; max_to_read > 0L; max_to_read--)
  {
    if ((ch= *str++ & 0x00FF) == 0) continue;
    byte_count++;

    rc= hyx_parse2_char (hps, le, ch, end_tags, end_tag_count);
/**
fprintf (stderr, "hyxp0008.c: parse2_char ch='%c' 0x%02X rc=%d cnt=%d\n",
 ch, ch, rc, end_tag_count);
**/
    if (rc != 0)
    {
      break;
    }
  }

STOP:
  *bytes_read= byte_count;

  return rc;
}

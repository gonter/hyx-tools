/*
 *  FILE 1996-02-11 12:59:28
 *
 *  read one lexicon entry
 *
 *  written:       1995-03-19
 *  latest update: 1996-02-11 12:59:39
 *  $Id: hyxp0005.c,v 1.3 2003/06/25 10:11:56 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/diagnose.h>

/* ------------------------------------------------------------------------ */
int hyx_parse2_file (
struct HYX_PARSER_STATUS *hps,
FILE *fi,                       /* file to be read from                     */
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

  if (bytes_read == (long *) 0 || le == (struct TEXT_ELEMENT **) 0)
  {
    gg_diagnose= LEX_RT_init_error;
    return -1;
  }

  if (max_to_read <= 0L) goto STOP;

  for (;; max_to_read--)
  {
    if (max_to_read > 0L)
    {
      ch= fgetc (fi) & 0x00FF;
      if (feof (fi))
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

    rc= hyx_parse2_char (hps, le, ch, end_tags, end_tag_count);
/**
fprintf (stderr, "hyxp0005.c: parse2_char ch='%c' 0x%02X rc=%d cnt=%d\n",
 ch, ch, rc, end_tag_count);
**/
    if (rc != 0)
    {
      if (rc > 0) rc= 0;
      break;
    }
  }

STOP:
  *bytes_read= byte_count;

  return rc;
}

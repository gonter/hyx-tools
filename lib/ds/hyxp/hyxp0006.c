/*
 *  FILE %ds/hyxp/hyxp0006.c
 *
 *  read one lexicon entry
 *
 *  written:       1991 03 26
 *  latest update: 1996-02-18 12:04:10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/diagnose.h>

/* ------------------------------------------------------------------------ */
int hyx_parse1_string (
struct HYX_PARSER_CLASS *hpc,
char *str,                      /* string to be read                        */
struct TEXT_ELEMENT **le,       /* datastructure to be built                */
long end_tags [],               /* set of possible end tags                 */
int end_tag_count,              /* number of possible endtags               */
long max_to_read,               /* number of bytes to be read at most       */
long *bytes_read)               /* number of bytes actually read            */
{
  struct HYX_PARSER_STATUS *hps;
  int rc;

  gg_diagnose= LEX_RT_no_frame_close;

  if ((hps= hyx_parser_reset (hpc)) == (struct HYX_PARSER_STATUS *) 0)
  {
    gg_diagnose= LEX_RT_init_error;
    return -1;
  }

  *le= (struct TEXT_ELEMENT *) 0;
  gg_diagnose= 0L;

  rc= hyx_parse2_string (hps, str, le, end_tags, end_tag_count,
                         max_to_read, bytes_read);

  free (hps);

  return rc;
}

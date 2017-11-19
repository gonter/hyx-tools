/*
 *  FILE %ds/hyxp/hyxp0004.c
 *
 *  read one lexicon entry
 *
 *  written:       1991 03 26
 *                 1996-06-09 10:52:52
 *  latest update: 2001-02-18 19:00:07
 *  $Id: hyxp0004.c,v 1.4 2002/01/22 03:07:35 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/diagnose.h>

/* ------------------------------------------------------------------------ */
int hyx_parse1_file (
struct HYX_PARSER_CLASS *hpc,
FILE *fi,                       /* file to be read from                     */
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

  rc= hyx_parse2_file (hps, fi, le, end_tags, end_tag_count,
                       max_to_read, bytes_read);

#ifdef PARSER_DEBUG
  printf (">>> hyxp0004: hps->HPS_tx_cnt= %ld\n", hps->HPS_tx_cnt);
  diag_display_markup (stdout, hpc, hps->HPS_tx_list, 1, 1, 1);
#endif /* PARSER_DEBUG */

  free (hps);

  return rc;
}

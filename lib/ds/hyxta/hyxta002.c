/*
 *  FILE %ds/hyxta/hyxta002.c
 *
 *  textual analysis:
 *  data stream segmentation
 *
 *  written:       1990 11 11
 *                 1994-12-24: isolated from ta003.c
 *                 1995-03-30: moved to %ds/hyxta
 *  latest udpate: 1996-12-22 18:30:14
 *
 */

#include <memory.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/ta.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
int hyx_ta_parse_flush (
struct HYX_PARSER_CLASS *hpc,
struct HYX_PARSER_STATUS *hps,
struct TEXT_ELEMENT **generated_node)
{
  struct TEXT_ELEMENT *te;

  if (hps->HPS_segment_length == 0L) return 0;       /* no data in buffer */

  if ((te= hyx_mktx_elem_and_segm (hpc, hps->HPS_segment,
                                   hps->HPS_segment_length,
                                   0L, TEt_text, 0, 0))
      == (struct TEXT_ELEMENT *) 0) return -1;

  te->TE_cat_flags= hps->HPS_cat_flags;
  *generated_node= te;

  hps->HPS_segment_length= 0L;
  hps->HPS_cat_flags= 0L;

  return 1;
}

/*
 *  FILE %ds/hyxp/hyxp0027.c
 *
 *  add character to text segment buffer
 *
 *  written:       1995-12-21
 *  latest update: 1995-12-21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/parse.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_parser_finish (struct HYX_PARSER_STATUS *lps)
{
  struct TEXT_SEGMENT *seg;

  if (lps == (struct HYX_PARSER_STATUS *) 0
      || (seg= hyx_parser_finish_segment (lps)) == (struct TEXT_SEGMENT *) 0
     )
    return (struct TEXT_ELEMENT *) 0;

  lps->HPS_text_alloc_flag= 0;

  return lps->HPS_tx_last;
}

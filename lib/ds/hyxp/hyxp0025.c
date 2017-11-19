/*
 *  FILE %ds/hyxp/hyxp0025.c
 *
 *  transfer flags from the parser context to a (newly created) text element
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
int hyx_transfer_details (
struct HYX_PARSER_STATUS *hps,
struct TEXT_ELEMENT *tt)
{
  if (hps == (struct HYX_PARSER_STATUS *) 0
      || tt == (struct TEXT_ELEMENT *) 0
     )
    return -1;

  tt->TE_type= hps->HPS_element_type;

  return 0;
}

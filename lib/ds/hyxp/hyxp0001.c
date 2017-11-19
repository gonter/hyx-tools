/*
 *  FILE %ds/hyxp/hyxp0001.c
 *
 *  initialize a virtual SGML parser
 *
 *  written:       1991-03-12
 *  latest update: 1996-02-18 10:47:20
 *
 */

#include <stdlib.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
struct HYX_PARSER_STATUS *hyx_parser_reset (struct HYX_PARSER_CLASS *hpc)
{
  struct HYX_PARSER_STATUS *hps;

  if ((hps= hyx_new_parser_status ()) != (struct HYX_PARSER_STATUS *) 0)
  {
    hps->HPS_hpc= hpc;

    hps->HPS_ptx= &hps->HPS_tx_list;
    hps->HPS_level_changed= 1;

    hps->HPS_last_cat_code= -1;
  }

  return hps;
}

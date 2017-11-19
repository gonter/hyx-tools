/*
 *  FILE %ta/ta020.c
 *
 *  written:       1994-03-25
 *                 1994-12-24: isolated from ta011.c
 *  latest update: 1999-11-28 13:28:39
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/parse.h>
#include <gg/ta.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_ta_flush_node_list (struct HYX_PARSER_STATUS *hps)
{
  if (hps->HPS_tx_list == (struct TEXT_ELEMENT *) 0) return 0;

  if (ta_print_paragraph (stdout, hps->HPS_tx_list, hps->HPS_tx_cnt) <= 0)
    hyx_frtx_elem_list (hps->HPS_tx_list);

  hps->HPS_tx_list= (struct TEXT_ELEMENT *) 0;
  hps->HPS_ptx= &hps->HPS_tx_list;
  hps->HPS_tx_cnt= 0L;

  return 0;
}

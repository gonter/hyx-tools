/*
 *  FILE %ds/hyxta/hyxta007.c
 *
 *  written:       1994-03-25
 *                 1994-12-24: isolated from ta011.c
 *                 1995-03-30: moved to %ds/hyxta
 *  latest update: 1996-12-22 18:50:12
 *
 */

#include <stdio.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
int hyx_ta_store_node (
struct HYX_PARSER_CLASS *hpc,
struct HYX_PARSER_STATUS *hps,
struct TEXT_ELEMENT *node)
{

#ifdef JUNK
  if (hps->HPS_tx_cnt > MAX_BUFFERED_NODES
      ||((node->TE_cat_flags & TA_CATF_space2)
        && hyx_tx_segm_count_char (node->TE_text_segment, '\n') > 1))
  {
    hyx_ta_flush_node_list (hps);
    printf ("\n\n");
    /****
    sgml_write_data (stdout, "", "", node->ta_data, (int) node->ta_data_size);
    ****/
  }

  if ((node->TE_cat_flags & TA_CATF_space2)
      && hyx_tx_segm_count_char (node->TE_text_segment, '\n') > 1)
    return 0;
#endif /* JUNK */

  node->TE_tag_definition= hyx_ta_find_tag_definition (hpc, node->TE_cat_flags);

  *hps->HPS_ptx= node;
  hps->HPS_ptx= &node->TE_next;
  hps->HPS_tx_cnt++;

  return 0;
}

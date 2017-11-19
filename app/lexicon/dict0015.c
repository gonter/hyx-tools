/*
 *  FILE %lexicon/dict0015.c
 *
 *  restructure text elements according to lexicon control
 *
 *  written:       1995-08-05
 *  latest update: 2001-02-18 18:04:53
 *  $Id: dict0015.c,v 1.2 2001/02/19 00:27:16 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_process_entry (
struct HYX_PARSER_CLASS *hpc,
struct HYX_CLUSTER_CONTROL *hcc,
struct LEXICON_CONTROL *lcc,
struct TEXT_ELEMENT *tx_new_entry,
hyx_output_processor *op,
void *op_client_data,
int verbose_level)
{
  char entry_key [ENTRY_KEY_SIZE];
  char index_str [24];
  char *frame_name;             /* name of the new frame                    */

if (tx_new_entry == (struct TEXT_ELEMENT *) 0)
{
fprintf (stdout, "warning: tx_new_entry == NIL 1\n");
return -1L;
}

/*****************
printf ("dict0015: tx_new_entry:\n");
print_text_element_list (stdout, tx_new_entry);
*****************/

  dict_restructure2_entry (hpc, lcc, &tx_new_entry, entry_key, ENTRY_KEY_SIZE);

  if (tx_new_entry == (struct TEXT_ELEMENT *) 0)
  {
    fprintf (stdout, "warning: tx_new_entry == NIL\n");
    return -1L;
  }

  if (*entry_key == 0)
  {
    fprintf (stdout, "warning: frame without <LE> markup; ignored ...\n");
    hyx_frtx_elem_list (tx_new_entry);
    return 1;
  }

  frame_name= dict_get_frame_name (hcc, entry_key, index_str);
  if (verbose_level > 0) printf ("%s %-27s ", frame_name, entry_key);

  return dict_update_entry (hpc, hcc, lcc, frame_name, tx_new_entry,
                            op, op_client_data, verbose_level);
}

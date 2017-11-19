/*
 *  FILE %lexicon/dict0008.c
 *
 *  repack frame index in YTREE info into ENTRY_DESCRIPTOR
 *  called by ytree_process
 *
 *  written:       1995-01-23
 *  latest update: 2000-08-26 15:17:40
 *  $Id: dict0008.c,v 1.2 2000/08/26 13:21:15 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int ytree_entry_descriptor_to_index (
struct YTREE *yt_node,
void *client_data)
{
  struct ENTRY_DESCRIPTOR *ed;

#ifdef MSDOS
  client_data;
#endif

  if ((ed= (struct ENTRY_DESCRIPTOR *) yt_node->YT_info)
      == (struct ENTRY_DESCRIPTOR *) 0
     || !(yt_node->YT_flags & YTflag_EOW))
    return 0;

  yt_node->YT_info= ed->ED_index;

  if (ed->ED_frame_name != (char *) 0) free (ed->ED_frame_name);
  if (ed->ED_te != (struct TEXT_ELEMENT *) 0)
    hyx_frtx_elem_list (ed->ED_te);

  free (ed);

  return 0;
}

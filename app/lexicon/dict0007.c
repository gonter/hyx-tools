/*
 *  FILE %lexicon/dict0007.c
 *
 *  repack frame index in YTREE info into ENTRY_DESCRIPTOR
 *  called by ytree_process
 *  opposite of dict0008.c
 *
 *  written:       1995-01-23
 *  latest update: 2000-08-26 15:17:27
 *  $Id: dict0007.c,v 1.2 2000/08/26 13:21:15 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int ytree_index_to_entry_descriptor (
struct YTREE *yt_node,
void *client_data)
{
  struct ENTRY_DESCRIPTOR *ed;

#ifdef MSDOS
  client_data;
#endif

  if (yt_node->YT_info == 0L || !(yt_node->YT_flags & YTflag_EOW)) return 0;

  if ((ed= (struct ENTRY_DESCRIPTOR *)
           calloc (sizeof (struct ENTRY_DESCRIPTOR), 1))
      == (struct ENTRY_DESCRIPTOR *) 0)
    return -1;

  ed->ED_index= yt_node->YT_info;
  ed->ED_status= ED_stat_from_LUT;
  yt_node->YT_info= (long) ed;

  return 0;
}

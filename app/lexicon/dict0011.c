/*
 *  FILE %lexicon/dict0011.c
 *
 *  written:       1995-03-11
 *  latest update: 1997-11-01 12:04:47
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_write_xfn_entry (struct YTREE *yt_node, void *client_data)
{
  struct ENTRY_DESCRIPTOR *ed;
  FILE *fo;

  if ((yt_node->YT_flags & YTflag_EOW)
      && (ed= (struct ENTRY_DESCRIPTOR *) yt_node->YT_info)
         != (struct ENTRY_DESCRIPTOR *) 0
      && ed->ED_frame_name != (char *) 0
      && (fo= (FILE *) client_data) != (FILE *) 0
     )
  {
    fprintf (fo, "%lx %s\n", ed->ED_index, ed->ED_frame_name);
  }

  return 0;
}

/*
 *  FILE ~/usr/nl_kr/lib/nl_00111.c
 *
 *  delete all references do a specified document from the
 *  associated with a certain word reference
 *
 *  written:       1993-02-28
 *  latest update: 1995-07-22
 *
 */

#include <gg/ytree.h>
#include <gg/lookup.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int lmd_discard_doc_id (struct YTREE *yt, void *client_data)
{
  struct WORD_REF *wr;

  if (yt != (struct YTREE *) 0
      && (wr= (struct WORD_REF *) yt->YT_info) != (struct WORD_REF *) 0)
  {
    ytree_process (wr->WR_ytree, lmd_discard_document_node, client_data);
  }
    
  return 0;
}

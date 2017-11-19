/*
 *  FILE %nl_kr/lib/nl_00133.c
 *
 *  insert a document in a list
 *
 *  written:       1995-04-01
 *  latest update: 1995-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO *lmd_insert_document_info (
struct WORD_REF *wr,
long doc_id,
char *doc_id_str)
{
  struct YTREE *yt;
  struct DOCUMENT_INFO *di;

  if ((di= lmd_new_document_info ()) != (struct DOCUMENT_INFO *) 0)
  {
    di->DI_document_id= doc_id;

    if ((yt= ytree_insert_word (&wr->WR_ytree, (unsigned char *) doc_id_str))
        != (struct YTREE *) 0)
    {
      yt->YT_info= (long) di;
      yt->YT_flags |= YTflag_EOW;
    }
  }

  return di;
}

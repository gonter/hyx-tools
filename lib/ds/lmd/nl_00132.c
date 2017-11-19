/*
 *  FILE ~/usr/nl_kr/lib/nl_00132.c
 *
 *  find a document in a list
 *
 *  written:       1995-04-01
 *  latest update: 1995-07-22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO *lmd_find_document_info (
struct WORD_REF *wr,
char *doc_id_str)
{
  struct YTREE *yt;

  if ((yt= ytree_lookup_word (wr->WR_ytree, (unsigned char *) doc_id_str))
      != (struct YTREE *) 0)
    return (struct DOCUMENT_INFO *) yt->YT_info;

  return (struct DOCUMENT_INFO *) 0;
}

/*
 *  FILE %ds/lmd/nl_00126.c
 *
 *  read a document info list
 *
 *  written:       1994-08-23
 *  latest update: 1996-08-08 17:22:59
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lmd_docid_list_insert (
struct DOCUMENT_INFO *element,
struct YTREE **wrl_ytree,
char *docid_str)
{
  struct YTREE *yt;

  if (element == (struct DOCUMENT_INFO *) 0) return -1;

#ifdef DEBUG
  printf ("nl_00126: docid_str='%s'\n", docid_str);
#endif

  if (wrl_ytree != (struct YTREE **) 0
      && (yt= ytree_insert_word (wrl_ytree, (unsigned char *) docid_str))
              != (struct YTREE *) 0)
  {
    yt->YT_flags |= YTflag_EOW;
    yt->YT_info= (long) element;
  }

  return 0;
}

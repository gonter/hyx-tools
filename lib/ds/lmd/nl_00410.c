/*
 *  FILE ~/usr/nl_kr/lib/nl_00410.c
 *
 *  data
 *  - functions to create LUTs -- using YTREE
 *  - see also: wordcr05.c (word reference system)
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *                 1994-12-19: isolated from wordcr04.c
 *  latest update: 1995-04-01
 *
 */

#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int ytree_wr_ptr2idx (struct YTREE *yt, void *lmdc)
{
  struct WORD_REF_LIST *wrl;

  lmdc; /* not used here but ytree_process passes data along */

  if ((wrl= (struct WORD_REF_LIST *) yt->YT_info)
      != (struct WORD_REF_LIST *) 0)
  {
    yt->YT_info= wrl->WRL_index;
  }

  return 0;
}

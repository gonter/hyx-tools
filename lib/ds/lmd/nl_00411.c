/*
 *  FILE ~/usr/nl_kr/lib/nl_00411.c
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
 *  latest update: 1995-07-16
 *
 */

#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int ytree_wr_idx2ptr (struct YTREE *yt, void *lmdc)
{
  long wrd_idx;

  if ((wrd_idx= yt->YT_info) >= 0L)
    yt->YT_info= (long) lmd_get_word_ref_list ((struct LMDC_CONTROL *) lmdc,
                                               wrd_idx);

  return 0;
}

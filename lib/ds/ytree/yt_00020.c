/*
 *  FILE %ds/ytree/yt_00020.c
 *
 *  ytree_alloc: create a new YTREE node
 *
 *  written:       1995-12-03
 *  latest update: 1995-12-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_repack (struct YTREE **ytp)
{
  struct YTREE *yt_new;
  struct YTREE *yt_old;

  if (ytp == (struct YTREE **) 0
      || (yt_old= *ytp) == (struct YTREE *) 0
      || (yt_new= ytree_duplicate (yt_old)) == (struct YTREE *) 0
     )
   return -1;

  *ytp= yt_new;
  ytree_free_node (yt_old);

  return 0;
}

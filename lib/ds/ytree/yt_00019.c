/*
 *  FILE %ds/ytree/yt_00019.c
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
struct YTREE *ytree_duplicate (
struct YTREE *yt)
{
  struct YTREE *yt_new;

  if (yt == (struct YTREE *) 0
      || (yt_new= ytree_alloc (yt->YT_str, yt->YT_lng_str))
          == (struct YTREE *) 0
     )
    return (struct YTREE *) 0;

  yt_new->YT_next= yt->YT_next;
  yt_new->YT_down= yt->YT_down;
  yt_new->YT_size= yt->YT_size;
  yt_new->YT_info= yt->YT_info;
  yt_new->YT_flags= yt->YT_flags;

  return yt_new;
}

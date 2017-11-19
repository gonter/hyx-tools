/*
 *  FILE %ds/ytree/yt_00018.c
 *
 *  ytree_set_value: set info pointer to a particular value
 *
 *  written:       1995-11-08
 *  latest update: 1995-11-08
 *  $Id: yt_00018.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
long ytree_get_value (struct YTREE *ytp, const unsigned char *w)
{
  struct YTREE *yt;

  if ((yt= ytree_lookup_word (ytp, (unsigned char *) w)) == (struct YTREE *) 0
      || !(yt->YT_flags & YTflag_EOW)
     ) return 0L;

  return yt->YT_info;
}

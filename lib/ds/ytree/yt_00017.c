/*
 *  FILE %ds/ytree/yt_00017.c
 *
 *  ytree_set_value: set info pointer to a particular value
 *
 *  written:       1995-11-08
 *  latest update: 1997-08-03 20:45:56
 *  $Id: yt_00017.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
long ytree_increment_value (struct YTREE **ytp, const unsigned char *w, long v)
{
  struct YTREE *yt;
  long v2= 0L;

  if ((yt= ytree_insert_word (ytp, (unsigned char *) w)) == (struct YTREE *) 0) return 0L;

  if (yt->YT_flags & YTflag_EOW)
  {
    v2= yt->YT_info;
    yt->YT_info += v;
  }
  else
  {
    yt->YT_info= v;
    yt->YT_flags |= YTflag_EOW;
  }

  return v2;
}

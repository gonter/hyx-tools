/*
 *  FILE %ds/ytree/yt_00016.c
 *
 *  ytree_set_value: set info pointer to a particular value
 *
 *  written:       1995-08-30
 *  latest update: 1996-01-07 23:59:20
 *  $Id: yt_00016.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
long ytree_set_value (struct YTREE **ytp, const unsigned char *w, long v)
{
  struct YTREE *yt;
  long v2= 0L;

  if ((yt= ytree_insert_word (ytp, (unsigned char *) w)) != (struct YTREE *) 0)
  {
    v2= yt->YT_info;
    yt->YT_info= v;
    yt->YT_flags |= YTflag_EOW;
  }

  return v2;
}

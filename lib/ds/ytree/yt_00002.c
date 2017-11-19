/*
 *  FILE %ds/ytree/yt_00002.c
 *
 *  free a complete ytree structure
 *
 *  written:       1990 11 12
 *                 1991 03 16: Revision; AIX
 *  latest update: 1995-08-20
 *  $Id: yt_00002.c,v 1.2 2001/11/20 19:32:44 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_free (struct YTREE *yt)
{
  struct YTREE *y;

  while (yt != (struct YTREE *) 0)
  {
    ytree_free (yt->YT_down);
    y= yt;
    yt= yt->YT_next;
    ytree_free_node (y);
  }

  return 0;
}

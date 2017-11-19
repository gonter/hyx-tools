/*
 *  FILE %ds/ytree/yt_00014.c
 *
 *  print a YTREE node for debugging reasons
 *
 *  written:       1994-12-11
 *  latest update: 1996-01-21 23:37:11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_debug (struct YTREE *yt)
{
  return ytree_print (stdout, yt, 2);
}

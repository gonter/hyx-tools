/*
 *  FILE %ned/07/ned0719b.c
 *
 *  swap two markers
 *  T2D: does not handle line callbacks
 *
 *  written:       1996-01-01
 *  latest update: 1997-09-07  9:41:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_swap_markers (struct MARKER *m1, struct MARKER *m2)
{
  struct MARKER tmp;

  if (m1 == (struct MARKER *) 0 || m2 == (struct MARKER *) 0) return -1;

  tmp.wptr= m1->wptr; tmp.ptr= m1->ptr; tmp.offset= m1->offset;
  m1->wptr= m2->wptr; m1->ptr= m2->ptr; m1->offset= m2->offset;
  m2->wptr= tmp.wptr; m2->ptr= tmp.ptr; m2->offset= tmp.offset;

  return 0;
}

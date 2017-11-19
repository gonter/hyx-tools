/*
 *  FILE %ned/07/ned0719c.c
 *
 *  swap two markers
 *
 *  written:       1996-01-01
 *  latest update: 1997-09-01 18:52:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_copy_markers (struct MARKER *dst, struct MARKER *src)
{
  if (dst == (struct MARKER *) 0 || src == (struct MARKER *) 0) return -1;

  ned_marker_rel_cb (dst->ptr, dst);

  dst->wptr= src->wptr;
  dst->ptr= src->ptr;
  dst->offset= src->offset;

  ned_marker_reg_cb (dst->ptr, dst);

  return 0;
}

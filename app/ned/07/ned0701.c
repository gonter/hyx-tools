/*
 *  FILE %ned/07/ned0701.c
 *
 *  set a marker at the given cursor position
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1997-09-07  9:30:49
 *  $Id: ned0701.c,v 1.2 2003/10/02 06:45:51 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_set_marker2 (
struct WINDOWCTRL *wc,          /* T2D: NULL is valid ?? */
struct LINE *lp,                /* T2D: NULL is valid ?? */
int offset,
struct MARKER *b)               /* T2D: NULL is valid ?? */
{
  if (b->ptr != (struct LINE *) 0) ned_marker_rel_cb (b->ptr, b);

  ned_marker_reg_cb (b->ptr= lp, b);
  b->offset= offset;
  b->wptr= wc;

  return 0;
}

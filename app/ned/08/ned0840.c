/*
 *  FILE %ned/08/ned0840.c
 *
 *  evaluate a marked block
 *
 *  written:       1991 05 23
 *  latest update: 2001-02-11 12:36:28
 *  $Id: ned0840.c,v 1.2 2001/02/12 00:03:33 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
void ned_eval_block ()
{
  if (ned_blk_invalid ()) return;
  ned_eval_line (b_beg.ptr, b_beg.offset, b_end.ptr, b_end.offset, 0);
}


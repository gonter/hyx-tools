/*
 *  FILE %ned/07/ned0718.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  T2D: retrieve b_beg, b_end using marker functions
 *
 *  written:       1987 04 08
 *                 1991 04 16: Revision
 *  latest update: 1997-09-28 10:36:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_beg, b_end;
extern struct MARKER b_first, b_last;
extern int block_mode, blk;

/* ------------------------------------------------------------------------ */
void ned_blk_rst ()
{
  ned_reset_block_flags (b_beg.wptr);

  b_beg.wptr=   b_end.wptr=   (struct WINDOWCTRL *) 0;
  b_beg.ptr=    b_end.ptr=    (struct LINE *) 0;
  b_beg.offset= b_end.offset= 0;

  b_first.wptr=   b_last.wptr=   (struct WINDOWCTRL *) 0;
  b_first.ptr=    b_last.ptr=    (struct LINE *) 0;
  b_first.offset= b_last.offset= 0;

  blk= 0;
}

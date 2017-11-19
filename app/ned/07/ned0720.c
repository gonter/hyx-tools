/*
 *  FILE %ned/07/ned0720.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 04 16: Revision
 *  latest update: 1996-05-27 18:06:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int blk;
extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
int ned_blk_invalid () /* 1 -> Block Marker inkonsistent oder unvollstaendig*/
{
  if (!blk              /* block not visible?? */
      || b_beg.wptr == (struct WINDOWCTRL *) 0
      || b_end.wptr == (struct WINDOWCTRL *) 0
      || b_beg.wptr != b_end.wptr
      || b_beg.ptr == (struct LINE *) 0
      || b_end.ptr == (struct LINE *) 0
      || (b_beg.ptr->line_flg & LINE_inBLOCK) == 0
      || (b_end.ptr->line_flg & LINE_inBLOCK) == 0
     ) return 1;

  return 0;
}

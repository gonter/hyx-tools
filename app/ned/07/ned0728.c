/*
 *  FILE %ned/07/ned0728.c
 *
 *  move a block
 *  - see also: ned_blk_iconify ()
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-09-07  9:40:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern struct WINDOWCTRL *aw;
extern struct MARKER b_beg, b_end;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_blk_move ()
{
  struct WINDOWCTRL *w_source;
  struct LINE *la, *lb;

  if (oper_level >= LEV_BLK
      || (aw->WC_edit_mode & EDIT_READ_ONLY)
      || aw->file_type == FTY_FTRWDW
      || ned_blk_invalid ()     /* T2D: b_beg and b_end checked therein     */
      || ned_blk_isolate2 (&b_beg, &b_end, (aw == b_beg.wptr)) == 0
     ) return;

  if ((w_source= b_beg.wptr) != aw)
    ned_w_jmp_aktline (w_source, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);

  la= b_beg.ptr;
  lb= b_end.ptr;

  ned_blk_insert3 (aw, la, lb, 0);
}

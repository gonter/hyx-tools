/*
 *  FILE %ned/07/ned0727.c
 *
 *  copy block
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-03-31 11:08:21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern struct MARKER b_beg, b_end;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_wc_blk_copy (struct WINDOWCTRL *wc, int before)
{
  struct LINE *la, *lb;

  if (oper_level >= LEV_BLK
      || wc == (struct WINDOWCTRL *) 0
      || (wc->WC_edit_mode & EDIT_READ_ONLY)
      || wc->file_type == FTY_FTRWDW
      || ned_blk_invalid ()
     ) return;

  ned_blk_duplicate (b_beg.ptr, b_end.ptr, &la, &lb,
                     b_beg.offset, b_end.offset, block_mode);

  ned_blk_insert3 (wc, la, lb, before);
}

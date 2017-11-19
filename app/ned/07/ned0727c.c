/*
 *  FILE %ned/07/ned0727c.c
 *
 *  copy block
 *
 *  written:       1997-03-31 (isolated from ned_wc_blk_copy)
 *  latest update: 1997-06-29 15:25:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_wc_buffer_copy (struct WINDOWCTRL *wc, int buffer_name, int before)
{
  struct LINE *la, *lb;
  struct NED_BUFFER *bu;

  if (oper_level >= LEV_BLK
      || wc == (struct WINDOWCTRL *) 0
      || (wc->WC_edit_mode & EDIT_READ_ONLY)
      || wc->file_type == FTY_FTRWDW
      || (bu= ned_get_buffer (buffer_name, 0)) == (struct NED_BUFFER *) 0
      || bu->l_beg == (struct LINE *) 0
     ) return;

  ned_blk_duplicate (bu->l_beg, bu->l_end, &la, &lb,
                     /*** bu->c_beg ***/ 0,
                     /*** bu->c_end ***/ bu->l_end->lng,  /* T2D !! */
                     BLOCK_MODE_line);

  ned_blk_insert3 (wc, la, lb, before);
}

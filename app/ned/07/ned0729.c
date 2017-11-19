/*
 *  FILE %ned/07/ned0729.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-09-07 10:12:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct MARKER b_beg, b_end;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_blk_delete ()
{
  if (oper_level >= LEV_BLK
      || (aw->WC_edit_mode & EDIT_READ_ONLY)
      || aw->file_type == FTY_FTRWDW
      || ned_blk_invalid ()     /* T2D: b_beg and b_end checked therein     */
      || ned_blk_isolate2 (&b_beg, &b_end, 0) == 0
     ) return;

  aw->f_upd= 1;
  aw->tlines= ned_cnt_total_lines (aw->WC_act);

  ned_store_line_to_buffer (0x00, b_beg.ptr, b_end.ptr, 0);

  ned_blk_rst ();

  ned_w_jmp_aktline (aw, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
}

/*
 *  FILE %ned/07/ned0713.c
 *
 *  set block begin and end markers
 *
 *  written:       1987 04 08
 *  latest update: 1997-09-28 10:31:25
 *  $Id: ned0713.c,v 1.2 2003/10/02 06:45:51 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_first, b_last;
extern int blk;
extern int block_mode;

/* ------------------------------------------------------------------------ */
void ned_set_block_markers (
struct WINDOWCTRL *wc,
struct LINE *lp,
int offset,
int what,               /* 0: first marker, 1: last marker                  */
int mode)               /* unless 0, change block mode                      */
{
  if (mode != 0) block_mode= mode;

  if (what == 0)
  {
    ned_reset_block_flags (b_first.wptr);       /* T2D: BUG HERE */
    ned_set_marker2 (wc, lp, offset, &b_first);
  }

  if (what == 0 || what == 1) ned_set_marker2 (wc, lp, offset, &b_last);

  ned_set_block_flags ();
  blk= 1;
  ned_display_window (wc);

  ned_fresh_buffer ();          /* make sure buffer is emptied */

#ifdef USE_TK
  ned_tk_block_export_flag (1);
#endif
}

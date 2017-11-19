/*
 *  FILE %ned/07/ned0750.c
 *
 *  mark complete window as a block
 *  T2D: this function is apparently not used anywhere
 *
 *  written:       1995-02-11
 *  latest update: 1997-09-07  9:30:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_blk_mark_all (struct WINDOWCTRL *w)
{
  struct LINE *lc;
  struct LINE *act;
  struct MARKER *mrk_beg;

  if (w == (struct WINDOWCTRL *) 0
      || (act= w->WC_act) == (struct LINE *) 0
     ) return -1;

  if ((mrk_beg= ned_get_marker (NED_MARKER_BEG, 1)) != (struct MARKER *) 0)
      ned_reset_block_flags (mrk_beg->wptr);

  lc= ned_find_first_line (act);
  ned_set_marker2 (w, lc, 0, mrk_beg);

  lc= ned_find_last_line (act);
  ned_set_marker2 (w, lc, 0, ned_get_marker (NED_MARKER_END, 1));

  ned_set_block_flags ();

  return 0;
}

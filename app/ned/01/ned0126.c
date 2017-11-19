/*
 *  FILE %ned/01/ned0126.c
 *
 *  isolate a word at the current cursor postition
 *
 *  written:       1991 10 23
 *                 1994-04-10: qq_isolate_word() isolated from here
 *  latest update: 1997-12-05 11:41:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int blk;

/* ------------------------------------------------------------------------ */
int q_isolate_word (char *wp, int max_lng, int charset, int go_left)
{
  struct LINE *lp;
  struct MARKER *mrk_beg;
  struct MARKER *mrk_end;
  int rc;
  int x;

  if ((lp= aw->WC_act) == (struct LINE *) 0) return 0;
  x= aw->cx - aw->ax + aw->hv;

  if (blk == 1
      && (mrk_beg= ned_get_marker (NED_MARKER_BEG, 0)) != (struct MARKER *) 0
      && mrk_beg->wptr == aw && mrk_beg->ptr == lp && mrk_beg->offset == x
      && (mrk_end= ned_get_marker (NED_MARKER_END, 0)) != (struct MARKER *) 0
      && mrk_end->wptr == aw && mrk_end->ptr == lp
      && ned_line_2_string (mrk_beg->ptr, mrk_beg->offset,
                        mrk_end->ptr, mrk_end->offset,
                        wp, max_lng, 0L, 0x0000) != (char *) 0
     )
    return strlen (wp);

  if ((rc= qq_isolate_word (wp, max_lng, charset, lp, x, lp->lng, go_left))
      > 0)
    return rc;

  return 0;
}

/*
 *  FILE %ned/02/ned0260c.c
 *
 *  vi emulation: set a marker
 *
 *  written:       1996-05-27
 *  latest update: 1997-07-04 16:10:32
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int ned_set_marker (struct WINDOWCTRL *wc, int marker_id)
{
  struct LINE *lp;
  int offset;

  if (wc == (struct WINDOWCTRL *) 0
      || (lp= wc->WC_act) == (struct LINE *) 0
     )
    return -1;

  offset= wc->cx + wc->hv - wc->ax;

  if (marker_id == '{') ned_set_block_markers (wc, lp, offset, 0, BLOCK_MODE_standard); else
  if (marker_id == '}') ned_set_block_markers (wc, lp, offset, 1, BLOCK_MODE_standard); else
  if (marker_id == '[') ned_set_block_markers (wc, lp, offset, 0, BLOCK_MODE_line); else
  if (marker_id == ']') ned_set_block_markers (wc, lp, offset, 1, BLOCK_MODE_line); else
  if (marker_id == '<') ned_set_block_markers (wc, lp, offset, 0, BLOCK_MODE_box); else
  if (marker_id == '>') ned_set_block_markers (wc, lp, offset, 1, BLOCK_MODE_box); else
  if (marker_id == '(') ned_set_block_markers (wc, lp, offset, 0, 0); else
  if (marker_id == ')') ned_set_block_markers (wc, lp, offset, 1, 0); else
  {
    struct MARKER *mrk;

    if ((mrk= ned_get_marker (marker_id, 1))==(struct MARKER *) 0) return -1;
    ned_set_marker2 (wc, lp, offset, mrk);
  }

  return 0;
}

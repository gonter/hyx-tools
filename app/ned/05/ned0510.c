/*
 *  FILE %ned/05/ned0510.c
 *
 *  delete the current line, primitive function
 *  see also: %ned/05/ned0510b.c
 *
 *  written:       1987 04 08: as del_line
 *                 1991 02 07: Revision
 *                 1991 05 26: Revision
 *                 1994-12-27: isolated delete_line and renamed
 *  latest update: 1999-05-01 10:36:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int COL_TEXT;
extern int blk;

/* ------------------------------------------------------------------------ */
void ned_delete_line () /* former p_delete_line */
{
  register struct WINDOWCTRL *w;        /* current window                   */
  int rc;
  int k;
  int blk_save;

  blk_save= blk;

  set_repeat_command (ned_delete_line);
  ned_wc_delete_line (aw, blk, COL_TEXT);
}

/* ------------------------------------------------------------------------ */
int ned_wc_delete_line (
register struct WINDOWCTRL *w,          /* current window                   */
int blk_save,
int col_text)
{
  int rc;
  int k;

  if ((rc= ned_delete_current_line (w)) <= 0) return -1;

  /* now display the whole mess...  scroll */
  if (rc == 3)
  { /* CLR_SINGLE_LINE: line was the only line on screen, blank screen...   */
    /* ### T2D ### maybe this could be optimized, but what the heck...      */
    w_setstring (0, w->ax, w->ay, w->bx, w->by, col_text, "", 0x03);
  }
  else
  if (rc > 0)
  {
    if (blk_save != blk)
    { /* p_refresh () */
      ned_display_window (w);
    }
    else
    {
      register struct LINE *lp;

      if (w->cy < w->by)
        w_scrblk_up (w->ax, w->cy, w->bx, w->by, w->attr_text, 1);

      lp= w->WC_act;
      for (k= w->cy; k < w->by; k++)
        if (lp != (struct LINE *) 0) lp= lp->next;

      wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);
      wd_displine (w, lp, k, w->ax, w->bx);
    }
  }

  ned_show_display_range (w);

  return 0;
}

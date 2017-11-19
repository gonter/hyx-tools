/*
 *  FILE %ned/05/ned0511.c
 *
 *  join two lines by calling ned_join2 () and displays the result
 *
 *  written:       1987 04 08
 *                 1990 05 20: Revision
 *                 1991 02 07: Revision
 *                 1991 05 26: Revision
 *  latest update: 1997-08-03  9:54:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_join3 (struct WINDOWCTRL *wc)
{
  struct LINE *lp;      /* current line */
  int k;

  if ((lp= wc->WC_act) == (struct LINE *) 0
      || wc->file_type == FTY_FTRWDW
      || lp->next == (struct LINE *) 0
      || ned_join2 (lp, lp->next) == -1
     ) return;

  wc->f_upd= 1;
  wc->tlines--;

  if (wc->ay != wc->cy || wc->first->prev == (struct LINE *) 0)
  {
    if (wc->cy+1 >= wc->by)
    {
      if (wc->cy+1 >= wc->by)
        wd_displine (wc, wc->WC_act->next, wc->by, wc->ax, wc->bx);
    }
    else
    {
      w_scrblk_up (wc->ax, wc->cy+1, wc->bx, wc->by, wc->attr_text, 1);
      for (k= wc->cy; k < wc->by; k++)
        if (lp != (struct LINE *) 0) lp= lp->next;
      wd_displine (wc, lp, k, wc->ax, wc->bx);
    }
  }

  wd_displine (wc, wc->WC_act, wc->cy, wc->ax, wc->bx);
  ned_show_display_range (wc);
}

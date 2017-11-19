/*
 *  FILE %ned/01/ned0111.c
 *
 *  flip to next page
 *
 *  written:       1987 04 08
 *  latest update: 1996-07-26  2:56:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_w_page_down (struct WINDOWCTRL *wc, int part)
{
  int i, lim;
  register struct LINE *lp;
  register struct LINE *lp_next;
  register struct LINE *lp_act;

  if (wc->WC_act              == (struct LINE *) 0
      || (lp= wc->first)      == (struct LINE *) 0
      || (lp_act= wc->WC_act) == (struct LINE *) 0
     ) return;

  lim= wc->by - wc->ay;
  if (part) lim /= 2;

  for (i= 0; i < lim; i++)
  {
    if ((lp_next= lp->next) == (struct LINE *) 0) break;
    wc->first= lp= lp_next;

    if (lp_act->next != (struct LINE *) 0)
    {
      wc->WC_act= lp_act= lp_act->next;
      wc->znr++;
    }
    else wc->cy--;
  }

  ned_display_window (wc);
}

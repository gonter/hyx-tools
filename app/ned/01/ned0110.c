/*
 *  FILE %ned/01/ned0110.c
 *
 *  page up
 *
 *  written:       1987 04 08
 *                 1991 05 27: Revision
 *  latest update: 1996-07-26  2:55:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_w_page_up (struct WINDOWCTRL *wc, int part)
{
  int i, lim;
  register struct LINE *lp;
  register struct LINE *lp_prev;

  if (wc->WC_act == (struct LINE *) 0) return;

  lim= wc->by - wc->ay;
  if (part) lim /= 2;
  lp= wc->first;

  /* ANM: Im Window sind wc->by - wc->ay + 1 Zeilen darstellbar ! */
  for (i= 0; i < lim; i++)
  {
    if ((lp_prev= lp->prev) == (struct LINE *) 0) break;
    wc->first= lp= lp_prev;
    wc->WC_act= wc->WC_act->prev;
    wc->znr--;
  }

  ned_display_window (wc);
}

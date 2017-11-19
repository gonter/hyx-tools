/*
 *  FILE %ned/02/ned0207.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 26: Revision
 *  latest update: 1997-09-14 10:59:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
int wd_upscr (struct WINDOWCTRL *wc)
{
  register struct LINE *lp;
  int i;

  if ((lp= wc->first) == (struct LINE *) 0) return 0;

  w_scrblk_up (wc->ax, wc->ay, wc->bx, wc->by, wc->attr_text, 1);

  for (i= wc->ay; i < wc->by; i++)
    if (lp != (struct LINE *) 0) lp= lp->next;

  wd_displine (wc, lp, i, wc->ax, wc->bx);
  if ((wc->znr % 20) == 1) ned_show_display_range (wc);

  return 1;
}

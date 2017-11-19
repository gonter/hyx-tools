/*
 *  FILE %ned/02/ned0209.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-09-14 11:06:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
void wd_dnscr (struct WINDOWCTRL *wc)
{
  w_scrblk_down (wc->ax, wc->ay, wc->bx, wc->by, wc->attr_text, 1);
  wd_displine (wc, wc->first, wc->ay, wc->ax, wc->bx);
  if ((wc->znr%20) == 1) ned_show_display_range (wc);
}

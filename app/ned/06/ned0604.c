/*
 *  FILE %ned/06/ned0604.c
 *
 *  Refresh Screen
 *
 *  written:       1987 04 08
 *                 1990 04 01: Revision
 *  latest update: 2000-08-25 19:30:24
 *  $Id: ned0604.c,v 1.2 2000/08/25 18:05:48 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
void p_refresh_all ()
{
  register struct WINDOWCTRL *wc;
  int wn= 1;

  ned_clear_screen ();

  for (wc= windows; wc != (struct WINDOWCTRL *) 0; wc= wc->WC_next)
  {
    wc->w_upd |= 0x04;
    wc->wc_window_number= wn++;
  }

  wda_setup ();
}

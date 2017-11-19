/*
 *  FILE %ned/06/ned0626.c
 *
 *  activate given window
 *
 *  written:       1991 09 03
 *  latest update: 1997-01-12 16:25:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;

/* ------------------------------------------------------------------------ */
void q0_jmpwdw (struct WINDOWCTRL *wc)
{
  if (wc == (struct WINDOWCTRL *) 0) return;

#ifdef USE_TK
  ned_tk_wc_window_action (wc, WC_action_deiconify);
#endif /* USE_TK */

  if (akt_page != wc->page) w_selpage (akt_page= wc->page);
  show_buttons (wc);

  /* if (wc->wflags & 0x01) */    /* Nur bei ueberlappenden Windows */
  {
    wc->w_upd |= 0x05;
    ned_display_window (wc);
  }
}

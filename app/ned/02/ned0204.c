/*
 *  FILE %ned/02/ned0204.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1990 01 28: Revision
 *                 1991 05 25: Revision
 *  latest update: 1997-06-14 19:37:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_display_window (struct WINDOWCTRL *w)
{
  if (w == (struct WINDOWCTRL *) 0) return;

  wd_2setup (w, w->ax, w->ay, w->bx, w->by);
  ned_decorate_window (w);

  setcup (w);
  w->w_upd= 0;                  /* clear window update flags                */
}

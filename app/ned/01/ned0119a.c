/*
 *  FILE %ned/01/ned0119a.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1996-05-23
 *  latest update: 1996-05-23 16:06:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_w_jmp_in_line (struct WINDOWCTRL *wc, int mode, int offset)
/* mode:                */
/* NEDJMP_BOLN   1:     */
/* NEDJMP_EOLN   2:     */
/* NEDJMP_AXLNG  3:     */
{
  int hvs;

#ifdef MSDOS
  offset;
#endif /* MSDOS */

  if (wc == (struct WINDOWCTRL *) 0
      || wc->WC_act == (struct LINE *) 0
      || wc->WC_act->lng == 0
     ) return;

  hvs= wc->hv;
  if (mode == NEDJMP_AXLNG)
    mode= (wc->cx + hvs == wc->ax) ? NEDJMP_EOLN : NEDJMP_BOLN;

#ifdef USE_TK
  tk_resetcup ();
#endif

  switch (mode)
  {
    case NEDJMP_BOLN:
      wc->cx= wc->ax;
      wc->hv= 0;
      break;

    case NEDJMP_EOLN:
      if (wc->WC_act->lng >= wc->bx - wc->ax)
      {
        wc->hv= wc->WC_act->lng - wc->bx + wc->ax;
        wc->cx= wc->bx;
      }
      else
        wc->cx= wc->WC_act->lng + wc->ax - wc->hv;
      break;
  }

  if (hvs != wc->hv) ned_display_window (wc);
}

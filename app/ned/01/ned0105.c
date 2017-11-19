/*
 *  FILE %ned/01/ned0105.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *  see also: %ned/01/ned0105a.c
 *
 *  written:       1987 04 08
 *  latest update: 1997-08-28 10:38:11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_w_cursor_left (register struct WINDOWCTRL *w, int num)
{
  if (w->WC_act == (struct LINE *) 0) return -1;

  while (num-- > 0)
  {
#ifdef USE_TK
    tk_resetcup ();
#endif

  if (w->hv + w->cx - w->ax > 0)
  {
    ned_q_cursor_left (w, 1);
  }
  else if (ned_w_cursor_up (w, 1) == 1)
  {
    w->cx= w->ax;
    if (w->WC_act->lng > w->bx - w->ax) p_ax_lng ();
    else w->cx= w->WC_act->lng + w->ax;
  }
  }

  return 0;
}

/*
 *  FILE %ned/01/ned0106.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *  see also: %ned/01/ned0106a.c
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *                 1991 09 15: Revision
 *  latest update: 1997-08-28 10:53:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_w_cursor_right (register struct WINDOWCTRL *w, int num)
{
  if (w->WC_act == (struct LINE *) 0) return -1;
#ifdef USE_TK
  tk_resetcup ();
#endif

  while (num-- > 0)
  if (w->hv + w->cx - w->ax < w->WC_act->lng)
  {
    ned_q_cursor_right (w, 1);
  }
  else
  {
    if (ned_w_cursor_down (w, 1) == 1)
    {
      w->cx= w->ax;
      if (w->hv)
      {
        w->hv= 0;
        ned_display_window (w);
      }
    }
  }

  return 0;
}

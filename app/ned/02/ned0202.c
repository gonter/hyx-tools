/*
 *  FILE %ned/02/ned0202.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-01-12 16:51:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

struct WINDOWCTRL *aw;
extern int akt_page;

/* ------------------------------------------------------------------------ */
void setcup (register struct WINDOWCTRL *w)
{
  register int l;

  if (w == (struct WINDOWCTRL *) 0) return;

  l= (w->WC_act == (struct LINE *) 0) ? 0 : w->WC_act->lng;

  if (w->hv + w->cx - w->ax >= l)
    w->cx= l - w->hv + w->ax;

  while (w->cx < 0)
  {
    w->hv -= w->cx;
    w->cx= 0;
  }

  if (w->hv < 0)
  {
    w->cx -= w->hv;
    w->hv= 0;
  }

  if (w->cx > w->bx || w->cy > w->by) return;
  w_setcup (akt_page, w->cx, w->cy);
}

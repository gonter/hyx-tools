/*
 *  FILE %ned/05/ned0514.c
 *
 *  elementare Editierfunktionen: TAB, NL, PGUP, PGDN
 *
 *  written:       1987 04 08
 *  latest update: 1997-06-28 22:46:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void pq_dn ()
{
  register struct LINE *lp1;
  register struct WINDOWCTRL *w;
  int zeile;
  int i;

  w= aw;
  ned_set_marker (w, '\'');
  if ((lp1= w->WC_act) == (struct LINE *) 0) return;
  zeile= w->znr;

  while (lp1->next != (struct LINE *) 0)
  {
    lp1= lp1->next;
    zeile++;
  }

  w->znr= zeile;
  w->WC_act= lp1;

  for (i= w->by - w->ay; i > 0; i--)
  {
    if (lp1->prev == (struct LINE *) 0) break;
    lp1= lp1->prev;
  }

  w->first= lp1;
  w->cy= w->by - i;
  ned_display_window (aw);
}

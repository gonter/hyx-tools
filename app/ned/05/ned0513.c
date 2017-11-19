/*
 *  FILE %ned/05/ned0513.c
 *
 *  elementare Editierfunktionen: TAB, NL, PGUP, PGDN
 *
 *  written:       1987 04 08
 *  latest update: 1997-06-28 22:46:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void pq_up ()
{
  register struct LINE *lp1;
  register struct WINDOWCTRL *w;

  ned_set_marker (aw, '\'');
  w= aw;
  if ((lp1= ned_find_first_line (w->WC_first)) == (struct LINE *) 0) return;

  w->WC_first= w->WC_act= lp1;
  w->znr= 1;
  w->cy= w->ay;
  ned_display_window (aw);
}

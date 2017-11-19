/*
 *  FILE %ned/03/ned0306.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1997-08-03  9:26:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_wc_delete (
struct WINDOWCTRL *w,
int df)         /* Display Flag: 1 -> Zeile anzeigen        */
{
  if (w == (struct WINDOWCTRL *) 0) return;

  qq_delete (w->WC_act, w->hv + w->cx - w->ax, 1);

  w->f_upd= 1;

  if (df) wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);
}

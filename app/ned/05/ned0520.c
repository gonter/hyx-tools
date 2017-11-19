/*
 *  FILE %ned/05/ned0520.c
 *
 *  Spalte in Zeile anspringen
 *
 *  written:       1991 07 01
 *  latest update: 1997-01-12 16:48:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int jmp2column (register struct WINDOWCTRL *w, int coln)
{
  int df= 0;

  if (coln < w->hv + w->ax || coln > w->hv + w->bx)
  { /* adjust hv */
    w->hv = coln-5;
    if (w->hv < 0) w->hv=0;
  }

  w->cx= coln+w->ax-w->hv;
  if (df) ned_display_window (w);
  setcup (w);

  return 0;
}

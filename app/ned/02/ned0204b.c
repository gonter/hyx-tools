/*
 *  FILE %ned/02/ned0204b.c
 *
 *  display the text section of a window
 *  T2D: hidden lines
 *
 *  written:       1987 04 08
 *                 1990 01 28: Revision
 *                 1991 05 25: Revision
 *  latest update: 1999-07-17 18:10:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
void wd_2setup (
struct WINDOWCTRL *w,
int xa,
int ya,
int xb,
int yb)
{
  register struct LINE *p;
  int i;

  p= w->first;

  if (ya < w->ay) ya= w->ay;
  if (yb > w->by) yb= w->by; /* clip */
  if (ya > yb) return;

  /* skip line pointer to first line drawn */
  for (i= w->ay; i < ya; i++)
    if (p != (struct LINE *) 0) p= p->next;

  /* display each line in region */
  for (i= ya; i <= yb; )
  {
    if (p != (struct LINE *) 0
        && (p->line_flg & LINE_HIDDEN)
        && i != ya                      /* show first line */
       )
      goto NEXT;

    wd_displine (w, p, i++, xa, xb);

    if (p != (struct LINE *) 0)
    {
NEXT:
      p= p->next;
    }
  }
}

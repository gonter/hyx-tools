/*
 *  FILE ~/usr/window/2/win_0202.c
 *
 *  written:       1989 09 09
 *  latest update: 1994-08-20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/window.h>

/* ------------------------------------------------------------------------ */
void wg_fbox (                          /* gefuelltes Rechteck              */
int x1,
int y1,
int x2,
int y2,
int col)
{
  register int x,y;

  if (x1 > x2) { x= x1; x1= x2; x2= x; }
  if (y1 > y2) { y= y1; y1= y2; y2= y; }

  for (y = y1; y <= y2; y++)
    _wg_x_line (x1, x2, y, col);
}

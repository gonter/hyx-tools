/*
 *  FILE ~/usr/window/2/win_0204.c
 *
 *  written:       1989 09 09
 *  latest update: 1994-08-20
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void wg_fcircle (               /* zeichnet Kreis mit Mittelpunkt           */
int xm,                         /* definiert durch (xm, ym)                 */
int ym,
int r,                          /* und Radius r                             */
int col)                        /* .. in der Farbe r                        */
{                               /* Alg: Bresenham modifiziert auf Kreisbahn */
  int x, y, dx, dy, e;
  int crit_y;                   /* critical lines */

  if (xm < 0 || ym < 0 || r < 0) return;

  x= 0;
  y= r;
  dy= x;
  dx= y;
  e= dx/2;

  do
  {
           _wg_x_line (xm-y, xm+y, ym-x, col);
    if (x) _wg_x_line (xm-y, xm+y, ym+x, col);
    if (ym-y != crit_y)
    {
             _wg_x_line (xm-x, xm+x, crit_y=ym-y, col);
      if (y) _wg_x_line (xm-x, xm+x,        ym+y, col);
    }

    x++;
    if (e < 0) { y--; e+= dx; dx= y; }
    dy= x;
    e-= dy;
  }
  while (dy <= dx);
}

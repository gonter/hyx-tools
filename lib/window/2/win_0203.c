/*
 *  FILE ~/usr/window/2/win_0203.c
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
void wg_circle (                /* zeichnet Kreis mit Mittelpunkt           */
int xm,                         /* definiert durch (xm, ym)                 */
int ym,
int r,                          /* und Radius r                             */
int col)                        /* .. in der Farbe r                        */
{                               /* Alg: Bresenham modifiziert auf Kreisbahn */
  int x, y, dx, dy, e;

  x= 0;
  y= r;
  dy= x;
  dx= y;
  e= dx/2;

  do
  {
    wg_wr_dot (xm+x,ym+y,col);
    wg_wr_dot (xm+y,ym+x,col);
    wg_wr_dot (xm-x,ym+y,col);
    wg_wr_dot (xm+y,ym-x,col);
    wg_wr_dot (xm+x,ym-y,col);
    wg_wr_dot (xm-y,ym+x,col);
    wg_wr_dot (xm-x,ym-y,col);
    wg_wr_dot (xm-y,ym-x,col);

    if (e < 0)
    {
      y--;
      e+= dx;
      dx= y;
    }

    dy= x++;
    e-= dy;
  }
  while (dy <= dx);
}

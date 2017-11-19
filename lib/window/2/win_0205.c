/*
 *  FILE ~/usr/window/2/win_0205.c
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
void _wg_x_line (
int ax,
int bx,
int y,
int col)
{
  int x;

  for (x= ax; x <= bx; x++)
    wg_wr_dot (x, y, col);
}

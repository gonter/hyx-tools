/*
 *  FILE ~/usr/window/2/win_0206.c
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
void _wg_y_line (
int x,
int ay,
int by,
int col)
{
  int y;

  for (y= ay; y <= by; y++)
    wg_wr_dot (x, y, col);
}

/*
 *  FILE ~/usr/window/1/win_0101.c
 *
 *  written:       1989 08 16: aus WIN1.SAR uebernommen
 *                             Revision
 *  latest update: 1994-12-25
 *
 */

#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

extern int W_TEXT_MAX_X;

void w_prntcol (int p, int x, int y, int a, char *s)
{
  while (*s)
  {
    if (x >= W_TEXT_MAX_X) break;
    w_setchar (p, x++, y, a, *s++);
  }
}

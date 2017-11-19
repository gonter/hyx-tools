/*
 *  FILE /usr/window/cga/win_0012.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y;

void cga_setchar (p, x, y, a, c)
int p, x, y, a, c;
{
  union REGS rega;
  union REGS regb;

  if (x < 0 || x >= W_TEXT_MAX_X ||
      y < 0 || y >= W_TEXT_MAX_Y) return;

  rega.h.ah = 2;
  rega.h.bh = p;
  rega.h.dl = x;
  rega.h.dh = y;
  int86 (0x10, &rega, &regb);

  rega.h.ah = 9;
  rega.h.bh = p;
  rega.x.cx = 1;
  rega.h.al = c;
  rega.h.bl = a;
  int86 (0x10, &rega, &regb);
}


/* ------------------------------------------------------------------------ */

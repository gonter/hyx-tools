/*
 *  FILE /usr/window/cga/win_0013.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y;

void cga_setnchar (p, x, y, a, c, n)
int p, x, y, a, c, n;
{
  union REGS rega;
  union REGS regb;

  if (x < 0 || x >= W_TEXT_MAX_X ||
      y < 0 || y >= W_TEXT_MAX_Y || n <= 0) return;
  if ((x+n) > W_TEXT_MAX_X) n = W_TEXT_MAX_X-x;

  rega.h.ah = 2;
  rega.h.bh = p;
  rega.h.dl = x;
  rega.h.dh = y;
  int86 (0x10, &rega, &regb);

  rega.h.ah = 9;
  rega.h.bh = p;
  rega.x.cx = n;     /* Wiederholfaktor */
  rega.h.al = c;
  rega.h.bl = a;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */

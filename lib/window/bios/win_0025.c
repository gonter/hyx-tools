/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0025.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

extern int W_GRAPH_MAX_X,
           W_GRAPH_MAX_Y;

int bios_rd_dot(x,y)  /* liest Punkt auf (x,y) mit Farbe col */
int x, y;
{
  union REGS rega;
  union REGS regb;

  if (x < 0 || x >= W_GRAPH_MAX_X ||
      y < 0 || y >= W_GRAPH_MAX_Y) return;

  rega.h.ah= 13;
  rega.x.dx= y;
  rega.x.cx= x;
  rega.h.bh= 0;
  int86 (0x10, &rega, &regb);
  return regb.h.al;
}

/* ------------------------------------------------------------------------ */

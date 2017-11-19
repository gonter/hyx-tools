/*
 *  FILE /usr/window/cga/win_0014.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

int cga_getchar (p, x, y)
int p, x, y;
{
  union REGS rega;
  union REGS regb;

    rega.h.ah = 2;
    rega.h.bh = p;
    rega.h.dl = x;
    rega.h.dh = y;
    int86 (0x10, &rega, &regb);

    rega.h.ah = 8;
    rega.h.bh = p;
    int86 (0x10, &rega, &regb);
    return regb.x.ax;
}

/* ------------------------------------------------------------------------ */

/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0014.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

int bios_getchar (p, x, y)
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

/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0042.C]
 *
 *  1990 05 16
 *
 */

#include <dos.h>
#pragma check_stack(off)

void bios_getcup (int p, int *x, int *y)
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 3;
  rega.h.bh = p;
  int86 (0x10, &rega, &regb);
  *x = regb.h.dl;
  *y = regb.h.dh;
}


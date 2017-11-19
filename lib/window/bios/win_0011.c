/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0011.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

void bios_border (col)
int col;
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 11;
  rega.h.bh = 0;    /* Colour Palette 0 */
  rega.h.bl = col;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */

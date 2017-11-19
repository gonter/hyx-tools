/*
 *  FILE ~/usr/window/bios/win_0009.c
 *
 *  written:       1989 08 16: aus WIN0.SAR Åbernommen
 *  latest update: 1994-05-09
 *
 */

#include <dos.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void bios_cursoroff ()
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 1;
  rega.h.ch = 0x38;
  rega.h.cl = 0x08;
  int86 (0x10, &rega, &regb);
}

/*
 *  FILE ~/usr/window/bios/win_0050.c
 *
 *  written:       1994-04-08: copied from win_0010.c
 *  latest update: 1994-05-09
 *
 */

#include <dos.h>

#ifdef MSDOS /* well... what else? */
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void bios_cursorsize (int lower, int upper)
{
  union REGS rega;
  union REGS regb;

  rega.h.ah= 1;
  rega.h.ch= lower;
  rega.h.cl= upper;
  int86 (0x10, &rega, &regb);
}

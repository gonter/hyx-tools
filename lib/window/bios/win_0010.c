/*
 *  FILE ~/usr/window/bios/win_0010.c
 *
 *  written:       1989 08 16: aus WIN0.SAR Åbernommen; Revision
 *  latest update: 1994-05-10
 *
 */

#include <dos.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void bios_cursoron ()
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 1;
  rega.h.ch = 0x06;
  rega.h.cl = 0x07;
  int86 (0x10, &rega, &regb);
}

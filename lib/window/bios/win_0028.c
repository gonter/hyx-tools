/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0028.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

void bios_set_col (what, col)           /* setzt Hintergrundfarbe resp.     */
int what, col;                          /* Farbpalette                      */
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 11;
  rega.h.bh = what;
  rega.h.bl = col;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */

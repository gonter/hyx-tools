/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0015.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *              Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void bios_setscreen (att)
int att;
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 6;
  rega.h.al = 0;
  rega.h.ch = rega.h.cl = 0;
  rega.h.dh = W_TEXT_MAX_Y-1;
  rega.h.dl = W_TEXT_MAX_X-1;
  rega.h.bh = att;
  int86 (0x10, &rega, &regb);
}

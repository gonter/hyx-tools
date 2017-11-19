/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0022.C]
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
bios_scrblk_down (ax, ay, bx, by, attr, cnt)
int ax, ay, bx, by, attr, cnt;
{
  union REGS rega;
  union REGS regb;

  if (bx < 0 || ax >= W_TEXT_MAX_X ||
      by < 0 || ay >= W_TEXT_MAX_Y) return;

  if (ax < 0) ax= 0;
  if (ay < 0) ay= 0;
  if (bx >= W_TEXT_MAX_X) bx=W_TEXT_MAX_X-1;
  if (by >= W_TEXT_MAX_Y) by=W_TEXT_MAX_Y-1;

  rega.h.ah = 7;
  rega.h.al = cnt;   /* clear window  */
  rega.h.ch = ay;
  rega.h.cl = ax;
  rega.h.dh = by;
  rega.h.dl = bx;
  rega.h.bh = attr;
  int86 (0x10, &rega, &regb);
  return 0;
}

/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0018.C]
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
void bios_setarea (p, ax, ay, bx, by, att)
int p, ax, ay, bx, by, att;
/* screen attribute auf page p im Bereich von [ax/ay, bx/by]   */
/* auf att setzen                                              */
{
  union REGS rega;
  union REGS regb;

  if (bx < 0 || ax >= W_TEXT_MAX_X ||
      by < 0 || ay >= W_TEXT_MAX_Y) return;

  if (ax < 0) ax= 0;
  if (ay < 0) ay= 0;
  if (bx >= W_TEXT_MAX_X) bx=W_TEXT_MAX_X-1;
  if (by >= W_TEXT_MAX_Y) by=W_TEXT_MAX_Y-1;

  rega.h.ah = 6;
  rega.h.al = 0;
  rega.h.ch = ay; rega.h.cl = ax;
  rega.h.dh = by;
  rega.h.dl = bx;
  rega.h.bh = att;
  int86 (0x10, &rega, &regb);
}

/*
 *  FILE %win/bios/win_0016.c
 *
 *                 1989 08 16: aus WIN0.SAR Åbernommen
 *                             Revision
 *  latest update: 1997-05-30 17:58:13
 *
 */

#include <gg/window.h>
#include <dos.h>
#pragma check_stack(off)

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y;

void bios_cls ()
/* screen attribute auf att setzen  */
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 6;
  rega.h.al = 0;
  rega.h.ch = rega.h.cl = 0;
  rega.h.dh = W_TEXT_MAX_Y-1;
  rega.h.dl = W_TEXT_MAX_X-1;
  rega.h.bh = WV_BRAUN | WH_SCHWARZ | W_HELL;
  int86 (0x10, &rega, &regb);
}

/*
 *  FILE /usr/window/bios/win_0020.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *              Revision
 *
 */

#include <dos.h>
#include <gg/window.h>
#pragma check_stack(off)

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
bios_scrolldown (w, cnt)
register struct WINDOW *w;
int cnt;
{
  union REGS rega;
  union REGS regb;

  rega.h.ah = 7;
  rega.h.al = cnt;   /* clear window  */
  rega.h.ch = w->ay+1;
  rega.h.cl = w->ax+1;
  rega.h.dh = w->by-1;
  rega.h.dl = w->bx-1;
  rega.h.bh = w->attr;
  int86 (0x10, &rega, &regb);
                /* passt cy NICHT an !!  */
  return 0;
}

/*
 *  FILE /usr/window/cga/win_0008.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *              Revision
 *
 */

#include <dos.h>
#include <gg/window.h>
#pragma check_stack(off)

extern int W_TEXT_AKT_MEM,
           W_AKT_MODE;

extern struct W_SCREEN_AND_MODES w_screen_and_modes;

/* ------------------------------------------------------------------------ */
void cga_selpage (p)
int p;
{ union REGS rega;
  union REGS regb;
  int mx;

  if (p < 0 ||
      p >= w_screen_and_modes.w_mode_capabilities [W_AKT_MODE].w_text_pages)
    return;

  switch (w_screen_and_modes.w_mode_capabilities [W_AKT_MODE].w_text_max_x)
  {
    case  40: mx = 0x0080; break;
    case  80: mx = 0x0100; break;
  }

  W_TEXT_AKT_MEM = 0xB800 + mx*p;

  rega.h.ah = 5;
  rega.h.al = p;
  int86 (0x10, &rega, &regb);
}

/*
 *  FILE /usr/window/bios/win_0008.c
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#include <gg/window.h>
#pragma check_stack(off)

extern struct W_SCREEN_AND_MODES w_screen_and_modes;

extern int W_AKT_MODE;

/* ------------------------------------------------------------------------ */
void bios_selpage (p)
int p;
{ union REGS rega;
  union REGS regb;

  if (p < 0 ||
      p >= w_screen_and_modes.w_mode_capabilities [W_AKT_MODE].w_text_pages)
    return;

  rega.h.ah = 5;
  rega.h.al = p;
  int86 (0x10, &rega, &regb);
}


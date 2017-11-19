/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0027.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#pragma check_stack(off)
#include <dos.h>

/* ------------------------------------------------------------------------ */
int bios_set_mode (int mode)            /* setzt Bildschirm Mode auf mode   */
/* RETIRN: 0 -> Modus gesetzt; -1 -> Modus nicht gesetzt                    */
{
  union REGS rega;
  union REGS regb;

  if (mode < 0) return -1;
  rega.h.ah = 0;
  rega.h.al = mode;
  int86 (0x10, &rega, &regb);
  return 0;
}


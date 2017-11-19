/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0029.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

int bios_blit_save (puffer, page, ax, ay, bx, by)
register char *puffer;
int   page, ax, ay, bx, by;
{
  union REGS rega1;
  union REGS rega2, regb;

  rega1.h.ah = 2;
  rega1.h.bh = page;
  rega2.h.ah = 8;
  rega2.h.bh = page;

  for (rega1.h.dl = ax; rega1.h.dl <= bx; rega1.h.dl++)
    for (rega1.h.dh = ay; rega1.h.dh <= by; rega1.h.dh++)
    {
      int86 (0x10, &rega1, &regb);
      int86 (0x10, &rega2, &regb);
      *puffer++ = (regb.h.al) & 0x00FF; /* Character    */
      *puffer++ = (regb.h.ah) & 0x00FF; /* Attribut     */
    }

}

/* ------------------------------------------------------------------------ */

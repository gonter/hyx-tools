/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0030.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#include <dos.h>
#pragma check_stack(off)

int bios_blit_load (puffer, page, ax, ay, bx, by)
register char *puffer;
int   page, ax, ay, bx, by;
{
  union REGS rega1;
  union REGS rega2, regb;

  rega1.h.ah = 2;
  rega1.h.bh = page;
  rega2.h.ah = 9;
  rega2.h.bh = page;
  rega2.x.cx = 1;

  for (rega1.h.dl = ax; rega1.h.dl <= bx; rega1.h.dl++)
    for (rega1.h.dh = ay; rega1.h.dh <= by; rega1.h.dh++)
    {
      rega2.h.al = *puffer++;   /* Character    */
      rega2.h.bl = *puffer++;   /* Attribut     */
      int86 (0x10, &rega1, &regb);
      int86 (0x10, &rega2, &regb);
    }

}

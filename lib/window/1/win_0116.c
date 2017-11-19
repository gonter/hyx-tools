/*
 *  FILE ~/usr/window/1/win_0116.c
 *
 *  written:       1989 08 16: aus WIN1.SAR uebernommen; Revision
 *  latest update: 1995-03-05
 *
 */


#include <dos.h>

int mapkey ()    /* nicht nur fuer windows!!, daher kein w_  */
/*  tastatur einlesen,
 *  sondercodes auf EIN integer abbilden
 *  usw...
 */
{
  int ch;
  union REGS ra, rb;

  ra.h.ah = 0x0000;             /* Fuer AT's: 0x0010 */
  int86 (0x0016, &ra, &rb);

  switch (rb.h.al)
  {
    case 0x00E0:
    case 0x0000: return (rb.h.ah & 0x00FF) | 0x0100;
    default    : return  rb.h.al & 0x00FF;
  }
}


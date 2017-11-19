/*
 *  FILE ~/usr/window/t2.c
 *
 *  written:       1990 03 03
 *  latest update: 1994-08-20
 *
 */

#include <bios.h>

main ()
{
  union REGS ra, rb;
  struct SREGS sr;
  int i;
  long get_info();

  ra.h.ah=0x12;
  ra.h.bl=0x10;
  int86x(0x10, &ra, &rb, &sr);
  printf ("bh=%02X bl=%02X ch=%02X cl=%02X\n",
          rb.h.bh, rb.h.bl, rb.h.ch, rb.h.cl);
  for (i=0; i < 20; i++)
  {
    printf ("cx=%04X dx=%04X %04X:%04X\n",
           get_info (i, 1), get_info (i, 0));
  }
}

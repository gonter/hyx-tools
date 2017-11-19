/*
 *  FILE %win/1/win_0124.c
 *
 *  written:       1994-09-04
 *  latest update: 1995-10-01
 *
 */

#include <stdio.h>
#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

static char block [256*3];

/* ------------------------------------------------------------------------ */
void w_set_332_palette ()
{
  int num= 0;
  int red;
  int green;
  int blue;
  int idx= 0;

  for (red= 0; red < 0x0040; red += 0x0008)
    for (green= 0; green < 0x0040; green += 0x0008)
      for (blue= 0; blue < 0x0040; blue += 0x0010)
      {
        block [idx++] = (char) red;
        block [idx++] = (char) green;
        block [idx++] = (char) blue;
        num++;
      }

  w_setpalette_block (0, 256, block);
}

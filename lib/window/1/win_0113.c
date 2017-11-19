/*
 *  FILE ~/usr/window/1/win_0113.c
 *
 *  written:       1989 08 16: aus WIN1.SAR Åbernommen; Revision
 *  latest update: 1995-03-05
 *
 */

#include <gg/window.h>

void gr_setcup (       /* 40-Zeichen-Cursor im Graphic Mode */
int cx, int cy)
{
  int i, j;

  for (i= 0; i < 2; i++)
    for (j= 0; j < 8; j++)
      wg_wr_dot (cx*8+j, cy*8+6+i, 0x81);
}


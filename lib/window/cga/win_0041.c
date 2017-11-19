/*
 *  FILE ~/usr/window/cga/win_0041.c
 *
 *  written:       1990 04 01
 *  latest update: 1994-12-24
 *
 */

#pragma check_stack(off)

extern int
  W_TEXT_MAX_X,
  W_TEXT_MAX_Y,
  W_TEXT_AKT_MEM;

void cga_cls_col (int col)
{
  int cnt;
  int *cp;

  cnt = W_TEXT_MAX_X * W_TEXT_MAX_Y;
  col = (col << 8) & 0xFF00;  /* Color Attribut + NULL-Blank */

  set_cp (&cp, 0x0000, W_TEXT_AKT_MEM);
  while (cnt-- > 0) *cp++ = col;
}

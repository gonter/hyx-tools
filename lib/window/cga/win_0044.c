/*
 *  FILE /usr/window/cga/win_0044.C
 *
 *  1991 07 05
 *
 */

#pragma check_stack(off)

extern int W_TEXT_AKT_MEM;
extern int W_TEXT_MAX_X;

/* ------------------------------------------------------------------------ */
void cga_blit_line (int page, int ax, int ay, int cnt, char *line)
{
  int off;
  char *cp;

  off = (ay*W_TEXT_MAX_X+ax)*2;

  set_cp (&cp, off, W_TEXT_AKT_MEM);
  memcpy (cp, line, cnt*2);
}

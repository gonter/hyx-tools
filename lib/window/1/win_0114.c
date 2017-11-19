/*
 *  FILE ~/usr/window/1/win_0114.c
 *
 *  written:       1989 08 16: aus WIN1.SAR uebernommen; Revision
 *  latest update: 1995-03-05
 *
 */

#include <gg/window.h>

void cga_setcup (  /* 40-Zeichen-Cursor im Graphic Mode */
int pag,
int cx,
int cy)
{
  gr_setcup (cx, cy);
}


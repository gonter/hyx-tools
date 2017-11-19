/*
 *  FILE C:\usr\window\win1.arc [WIN_0121.C]
 *
 *  1989 08 19: aus COMMON.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void  w_display_scr (page, scr)
int   page;
char *scr;
{
  int i, j;

  j = VAL (scr,0);

  for (i = 2; i < j; i += scr [i] & 0x00FF)
      w_display (page, &scr [i]);
}

/*
 *  FILE C:\usr\window\win1.arc [WIN_0103.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void w_create (struct WINDOW *w)
{
  int i;

  w_clear     (w);
  w_disp_bbox (w->page, w->ax, w->ay, w->bx, w->by, w->attr, 2);

  w->cx = w->ax+1; w->cy = w->ay+1;
  w_setcup (w->page, w->cx, w->cy);
}


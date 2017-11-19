/*
 *  FILE C:\usr\window\win1.arc [WIN_0104.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

void w_namecreat (w, n)
struct WINDOW *w;
char *n;
{ int i;

  w_create (w);

  for (i = w->ax + 1; i < w->bx && n [i - w->ax-1]; i++)
      w_setchar (w->page, i, w->ay, w->attr, n [i - w->ax-1]);
  w_setcup (w->page, w->cx, w->cy);
}


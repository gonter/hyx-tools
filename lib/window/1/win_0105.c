/*
 *  FILE C:\usr\window\win1.arc [WIN_0105.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

void gr_create (w)
struct WINDOW *w;
{ int i;

  wg_box (w->ax*8+6, w->ay*8+6,
          w->bx*8+1, w->by*8+1,
          w->attr);
  wg_box (w->ax*8+4, w->ay*8+4,
          w->bx*8+3, w->by*8+3,
          w->attr);
}


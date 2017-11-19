/*
 *  FILE C:\usr\window\win1.arc [WIN_0107.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

void w_putln (w, l)
struct WINDOW *w;
char *l;
/*  String l in einer Zeile ausgeben bis
 *  a) Window Zeile aus
 *  b) Zeile im String aus
 *  c) String aus
 *  und einen Zeilenevorschub durchfuehren (ggf. scrollen)
 */
{
  w_put1ln (w, l);
  if (w->cy >= w->by)
     w_scrollup (w, 1);
  w_setcup (w->page, w->cx, w->cy);
}


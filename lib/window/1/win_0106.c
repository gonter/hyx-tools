/*
 *  FILE C:\usr\window\win1.arc [WIN_0106.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

void w_put1ln (w, l)
struct WINDOW *w;
char *l;
/*  String l in einer Zeile ausgeben bis
 *  a) Window Zeile aus
 *  b) Zeile im String aus
 *  c) String aus
 */
{
  if (w->cy >= w->by)
   {
     w_scrollup (w, w->cy - w->by + 1);
   }

  for (;;)
   {
     if (w->cx >= w->bx) break; /* fall a) */
     if ((*l == 0x00) || (*l == 0x0D) || (*l == 0x0A))
        break; /* fall b) und c)  */
     w_setchar (w->page, (w->cx)++, w->cy, w->attr, *l++);
   }

  if (w->cx < w->bx)
     w_setnchar (w->page, w->cx, w->cy, w->attr, ' ', w->bx - w->cx);
  (w->cy)++; w->cx = w->ax + 1;

}


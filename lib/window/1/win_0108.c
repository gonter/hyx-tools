/*
 *  FILE C:\usr\window\win1.arc [WIN_0108.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

void w_putstr (w, s)
struct WINDOW *w;
char *s;
{
  while (*s)
   { if (w->cy == w->by) w_scrollup (w, 1);
     if (w->cx == w->bx)
      { (w->cy)++; w->cx = w->ax + 1;
        continue;
      }
     if ((*s == 0x0D) || (*s == 0x0A))
      { (w->cy)++; w->cx = w->ax +1; s++;
        continue;
      }
     w_setchar (w->page, (w->cx)++, w->cy, w->attr, *s++);
   }
  if (w->cy >= w->by)
   { w_scrollup (w, 1);
   }
  w_setcup (w->page, w->cx, w->cy);
}


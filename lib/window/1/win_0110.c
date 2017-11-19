/*
 *  FILE C:\usr\window\win1.arc [WIN_0110.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

int w_readln (w, s)    /* bis end of line zeichen oder wendiger  */
struct WINDOW *w;
char *s;
/* return: last uninterpreted key  */
{ int si = 0, ch;
/*  printf ("READ: cx %d cy %d ax %d ay %d bx %d by %d\n",
 *          w->cx, w->cy, w->ax, w->ay, w->bx, w->by);
 */

  for (;;)
  { if (w->cx <= w->ax) w->cx = w->ax + 1;
    if (w->cx >= w->bx) return 0;
    if (w->cy <= w->ay) w->cy = w->ay + 1;
    if (w->cy >= w->by)
     { w_scrollup (w, w->cy - w->by + 1);
       continue;
     }
    /* eventuell cursor setzen  */
    w_setchar (w->page, w->cx, w->cy, w->attr, ' ');
    ch = mapkey ();
    if ((ch >= 0x0020) && (ch <= 0x00FF))
     { w_setchar (w->page, w->cx++, w->cy, w->attr, ch);
       s [si++] = ch;
     }
    else
    switch (ch)
    { case 0x000D:
      case 0x000A: w->cy++;
                 w->cx = w->ax + 1;
                 s [si] = 0;
                 if (w->cy >= w->by)
                    w_scrollup (w, 1);
                 w_setcup (w->page, w->cx, w->cy);
                 return 0x0A;
      case 0x0008: /* backtab  */
                 if (w->cx <= w->ax + 1) break;
                 w->cx--; si--;
                 break;
#ifdef JUNK
      case 0x0141:
      case 0x0143: /* F7 u. F9 */
                 s [si] = 0;
                 return 0;
#endif
      /* andere interpretationen usw */
      default: s [si] = 0;
               return ch;
    }
  }
}


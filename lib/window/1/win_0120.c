/*
 *  FILE C:\usr\window\win1.arc [WIN_0120.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
/* Anzeigen von Screen Records im Text Modus                                */
void  w_display (page, s)
int   page;                     /* verwendete Bildschirmseite               */
char *s;                        /*  Screen Record                           */
{ int i, l, cx, cy, attr;

  l    = s [0] & 0x00FF;
  cx   = s [1] & 0x00FF;
  cy   = s [2] & 0x00FF;
  attr = s [3] & 0x00FF;
#ifdef DEBUG
    printf ("\ncx=%d, cy=%d, laenge=%d, attr=0x%02x",
               cx, cy, l, attr);
#endif

  if (cx == 255)
   { switch (cy)
     { case 0x01: /* set background colour               */
                  w_setscreen (attr);
                  if (l > 4) w_border (s [4]);
                  break;
       case 0x02: /* Area                                */
                  w_scrblk_up (s [4] & 0x00FF,
                               s [5] & 0x00FF,
                               s [6] & 0x00FF,
                               s [7] & 0x00FF,
                               attr, 0);
                  break;
       case 0x03: /* Doppelte Box                        */
       case 0x04: /* Einfache Box                        */
                  w_disp_bbox (page, s [4] & 0x00FF, s [5] & 0x00FF,
                               s [6] & 0x00FF, s [7] & 0x00FF, attr,
                               (cy==3) ? 2 : 1);
                  break;
       case 0xFF: /* defined as the empty screen object    */
                  break;
     }
   }
  else
    for (i = 4; i < l; i++)
        w_setchar (page, cx++, cy, attr, s [i]);
}

/*
 *  FILE C:\usr\window\win1.arc [WIN_0119.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

w_puts (str)
char *str;
{ int i = 0;
  int Cx=0, Cy=0, Cm=0;               /* ####aktuelle Cursor Position ####*/

  for (i = 0; str [i]; i++)
      switch (str [i])
      { case 0x07: break;
        case 0x08: if (Cx) Cx--;
                   else if (Cy)
                           { Cx = (Cm) ? 39 : 79;
                             Cy--;
                           }
                   break;
        case 0x0C: Cx = Cy = 0; break;
        case 0x0D: case 0x0A:
                   Cx = 0;
                   if (++Cy >= 25)
                      Cy = 0;
                   break;
        default: w_setchar (0, Cx, Cy, WV_GRUEN, str [i]);
                   if (++Cx >= ((Cm) ? 40 : 80))
                      { Cx = 0;
                        if (++Cy >= 25)
                           Cy = 0;
                      }
                 break;
      }
}





/*
 *  FILE C:\usr\window\win1.arc [WIN_0115.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

void ega_setcup (pag, cx, cy)  /* 80-Zeichen-Cursor im EGA Mode */
int pag, cx, cy;
{ int i, j;
       for (i = 0; i < 2; i++)
           for (j = 0; j < 8; j++)
               wg_wr_dot (cx*8+j, cy*14+12+i, 0x81);
}


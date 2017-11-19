/*
 *  FILE %win/1/win_0102.c
 *
 *  written:       1989 08 16: extracted from WIN1.SAR; revision
 *  latest update: 1995-09-30
 *  $Id: win_0102.c,v 1.2 2005/09/04 20:27:37 gonter Exp $
 *
 */

#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void w_setstring (
int p,                      /* Bildschirmseite                       */
int ax,                     /* ) Stringausgabewindow                 */
int ay,
int bx,                     /* )                     (inklusiv)      */
int by,
int a,                      /* Attribut aller Chars                  */
const char *s,              /* What's to print on screen             */
int f)                      /* Bit 0: -> angefangene Zeile loeschen  */
                            /*     1: -> restliches Window loeschen  */
{
  int cx, cy;

  for (cy= ay; cy <= by; cy++)
    for (cx= ax; cx <= bx; cx++)
      if (*s)
        w_setchar (p, cx, cy, a, *s++);
      else
      {
        if ((f & 0x01) || (f & 0x02))
          w_setnchar (p, cx, cy, a, ' ', bx - cx + 1);
        if (f & 0x02) break;      /* in die Zeilenschleife */
        else return;
      }
}

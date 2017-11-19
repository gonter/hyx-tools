/*
 *  FILE ~/usr/window/palette.c
 *
 *  written:       1990 01 20
 *  latest update: 1994-08-20
 *
 */

#define W_MODEL_BIOS
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
int main ()
{
  int R= 20, G= 20, B= 20;
  int k;

  w_init (0x0000);
  for (;;)
  {
    w_setpalette (61, R, G, B);
    w_prntcol (0,0,3, 13, "ллллллллл");
    w_setcup  (0,0,4);
    printf ("R: %3d  G: %3d  B: %3d\n", R, G, B);
    printf ("R:  %02X  G:  %02X  B:  %02X\n", R, G, B);
    printf ("X: Exit\n");
    k= kbin ();
    if (k == 'x') break;
    switch (k)
    {
      case 'r': R--; if (R <  0) R= 0; break;
      case 'R': R++; if (R > 63) R=63; break;
      case 'g': G--; if (G <  0) G= 0; break;
      case 'G': G++; if (G > 63) G=63; break;
      case 'b': B--; if (B <  0) B= 0; break;
      case 'B': B++; if (B > 63) B=63; break;
    }
  }
}

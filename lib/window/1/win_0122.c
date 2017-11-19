/*
 *  FILE ~/usr/window/1/win_0122.c
 *
 *  written:       1990 04 21: aus /usr/fm/files.c uebernommen
 *  latest update: 1994-08-20
 *
 */

#include <gg/window.h>
#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void w_prtstr (
int p,
int x,
int y,
int attr, 
char *nm,
int l)                  /* Laenge des zu beschreibenden Feldes   */
                        /* l < 0 -> Rechtsbuendig                */
{
  int i, j= 0;

  if (nm == (char *) 0)
  {
    w_setnchar (p, x, y, attr, ' ', l);
    return;
  }

  if (l < 0)
  {
    j= strlen (nm);
    for (i= 0; i > l; i--)
      w_setchar (p, x+i, y, attr, (j > 0) ? nm [--j] : ' ');
  }
  else
  {
    for (i= 0; nm [i] && i < l; i++)
      w_setchar (p, x+i, y, attr, nm [i]);
    if (i < l) w_setnchar (p, x+i, y, attr, ' ', l-i);
  }
}

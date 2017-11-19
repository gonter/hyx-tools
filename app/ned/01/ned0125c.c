/*
 *  FILE %ned/01/ned0125c.c
 *
 *  written:       1991 06 01
 *  latest update: 1997-10-26  9:10:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#define CHAR_HOLLOW ':'
#define CHAR_FULL   '#'

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;
extern int NED_TEXT_MAX_X;

/* ------------------------------------------------------------------------ */
int ned_ch_show_display_range (struct WINDOWCTRL *w)
{
  int zpb;              /* number of lines represented by each block        */
  int dlines;           /* Zahl der Zeilen im Window                        */
  int xlines;           /* Zahl der Zeilen im File                          */
  int first_line;       /* Nummer der 1. Zeile am Schirm                    */
  int hollow= 0;        /* Zahl der schattierten Zeilen am Anfang           */
  int full;             /* Zahl der ausgefuellt angezeigten Zeilen          */
  int x, y;             /* Koordinaten am Window Rand                       */
  int a;                /* Colour Attribute der Anzeige                     */

  if (w == (struct WINDOWCTRL *) 0) return -1;
  if (w->box_type == BOX_TYPE_none
      || (x= w->bx+1) >= NED_TEXT_MAX_X
     ) return 0;

  xlines= w->tlines;
  first_line= w->znr - w->cy + w->ay;
  if (xlines <= 0 || first_line > xlines)
  { /* xlines unplausibel; fehlerhafte Berechnung??? */
    xlines= w->tlines= ned_cnt_total_lines (w->WC_act);
    /**** first_line= ned_cnt_line_2beg (w->first); ****/
  }

  dlines= w->by - w->ay + 1;

  zpb= xlines/dlines;
  if (zpb<=0)
  {
    hollow= 0;
    full=   dlines;
  }
  else
  {
    hollow= first_line/zpb;
    full=   dlines/zpb;
    if (full <= 0) full=1;
  }

  /* x= w->ax-1 */
  y= w->ay;
  a= w->attr_box;

  for (; y <= w->by && hollow-- > 0; y++)
    w_setchar (akt_page, x, y, a, CHAR_HOLLOW);
  for (; y <= w->by && full--   > 0; y++)
    w_setchar (akt_page, x, y, a, CHAR_FULL);
  for (; y <= w->by;                 y++)
    w_setchar (akt_page, x, y, a, CHAR_HOLLOW);

  return 0;
}

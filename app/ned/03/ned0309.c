/*
 *  FILE %ned/03/ned0309.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1996-07-26  3:28:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int akt_page;
extern int COL_SCROLL;

/* ------------------------------------------------------------------------ */
void wd_coldis (
register struct WINDOWCTRL *w,
int  la,                         /* 1. Zeile im Window                  */
int  lz,                         /* letzte Zeile(#); Inklusive          */
struct LINE *lp,                 /* 1. anzuzeigende Zeile               */
int  coln,                       /* # des Zeichens im Text              */
int  colpos)                     /* Spalten # fuer Ausgabe              */
/* ANM: diese Funktion scheint jetzt zu funktionieren siehe p_ins ()    */
{
  int ch;
  int att;

  att= (w == (struct WINDOWCTRL *) 0) ? COL_SCROLL : w->attr_text;

  for (;;)
  {
    if (lp == (struct LINE *) 0) w_setchar (0, colpos, la, att, ' ');
    else
    {
      if (lp->ftr != (struct FEATURE *) 0 || (lp->line_flg & LINE_inBLOCK))
      { /* #### Korrekte Ausgabe der Farben ginge sicher effizienter! ##### */
        wd_displine (w, lp, la, w->ax, w->bx);
      }
      else
      {
        ch= get_txt (lp, coln);
        w_setchar (akt_page, colpos, la, att, (ch == -1) ? ' ' : ch);
      }
      lp= lp->next;
    }
    if (la++ == lz) break;
  }
}

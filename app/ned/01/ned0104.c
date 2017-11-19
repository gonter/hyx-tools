/*
 *  FILE %ned/01/ned0104.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 05 27: Revision
 *  latest update: 1996-07-26  2:42:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void chk_updown (register struct WINDOWCTRL *w)
{
  register struct LINE *l;
  struct FEATURE **fp;

  if (w == (struct WINDOWCTRL *) 0
      || (l= w->WC_act) == (struct LINE *) 0
     ) return;

  if (l->lng < w->hv)
  {
    w->hv= l->lng - TXT_LNG;
    if (w->hv < 0) w->hv= 0;
    ned_display_window (w);
  }

  /* EXP: 1996-03-10 13:13:58 */
  if ((fp= ned_feature_find2 (w, 1)) != (struct FEATURE **) 0)
    show_feature (*fp);
}

/*
 *  FILE %ned/10/ned1017.c
 *
 *  Maus Steuerung
 *
 *  written:       1995-10-19
 *  latest update: 1997-10-26 10:22:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include <gg/maus.h>
#include <gg/keys.h>
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
/* richtiges Window suchen und ggf. anspringen                              */
/* return:                      */
/* 0 ... cursor within window   */
/* 1 ... frame                  */
/* 2 ... cursor out of window   */
int ned_mouse_set_cursor (int x, int y)
{
  int dy, dy2;
  int rv= 0;

#ifdef USE_TK
  tk_resetcup ();
#else
  if (x+1 < aw->ax || x-1 > aw->bx ||
      y+1 < aw->ay || y-1 > aw->by)
  { /* Cursor ausserhalb der Grenzen des aktuellen Windows       */
    /* -> anderes Window                                         */
    maus_jmpwdw (x, y);
  }
#endif /* !USE_TK */

  if (x < aw->ax-1 || x > aw->bx+1
      || y < aw->ay-1 || y > aw->by+1
     )
    return 2;

  if (x < aw->ax || x > aw->bx
      || y < aw->ay || y > aw->by
     )
    rv= 1;

  for (dy2= 0; (dy= aw->cy - y) && dy != dy2; dy2= dy)
    if (dy > 0) ned_cursor_up (); else ned_cursor_down ();

  if (x >= aw->ax && x <= aw->bx)
  {
    aw->cx= x;
    setcup (aw);
  }
  else
  if (x+1 == aw->ax && aw->hv)
  {
    aw->cx= aw->ax;
    ned_cursor_left ();
  }
  else
  if (x-1 == aw->bx)
  {
    aw->cx= aw->bx;
    setcup (aw);
    if (aw->cx-aw->ax+aw->hv < aw->WC_act->lng)
    {
      ned_cursor_right ();
    }
  }

  return rv;
}

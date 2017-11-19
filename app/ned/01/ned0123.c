/*
 *  FILE %ned/01/ned0123.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 01 31: Revision
 *  latest update: 1997-08-03  9:14:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern struct WINDOWCTRL *aw;
extern int akt_page;

/* ---------------------------------------------------------------------- */
void ned_del_char_left ()
{
  int flg= 0;

  if (aw->WC_act == (struct LINE *) 0
      || (aw->WC_edit_mode & EDIT_READ_ONLY)
     ) return;

#ifdef USE_ABBREVIATIONS
  ned_abbrev_reduce ();
#endif /* USE_ABBREVIATIONS */

  if (aw->cx - aw->ax == 0)
  { /* cursor at left side of the screen */

    if (aw->hv > 0)
    { /* horizontal view can be shifted */
      ned_q_cursor_left (aw, 1);
      goto DEL;
    }

    if (aw->WC_act->prev == (struct LINE *) 0) return;
    aw->WC_act= aw->WC_act->prev;

    if (aw->cy == aw->ay)    /* gdw. aw->WC_act == aw->first !! */
         aw->first= aw->first->prev;
    else aw->cy--;

    if (aw->WC_act->lng > aw->bx - aw->ax)
    {
      aw->hv= aw->WC_act->lng;
      aw->cx= aw->ax;
      flg= 1;
    }
    else
    {
      aw->cx= aw->WC_act->lng + aw->ax;
      aw->hv= 0;
    }

    ned_join3 (aw);
    aw->znr--;
    if (flg) ned_display_window (aw);
  }
  else
  {
    aw->cx--;
DEL:
    ned_wc_delete (aw, 1);
  }
}

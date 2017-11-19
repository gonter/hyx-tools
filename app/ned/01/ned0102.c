/*
 *  FILE %ned/01/ned0102.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-09-14 11:06:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int ned_vertical_scroll_count;

/* ------------------------------------------------------------------------ */
int ned_w_cursor_up (
register struct WINDOWCTRL *w,
int num)
{
  register struct LINE *l;
  int cnt= 0;

  for (; num > 0; num--)
  {
#ifdef USE_TK
    tk_resetcup ();       /* T2D: specify correct window! */
#endif

    if ((l= w->WC_act) == (struct LINE *) 0) break;

    if (l->prev == (struct LINE *) 0)
    {
      ned_show_display_range (w);
      return 0;
    }

    if (w->cy > w->ay)
    {
      w->cy--;
      w->WC_act= l= l->prev;
    }
    else
    {
      if (ned_vertical_scroll_count <= 1)
      {
        w->WC_act= w->first= l= w->first->prev;
        wd_dnscr (w);
      }
      else
      {
        ned_w_page_up (w, 0);
        l= w->WC_act;
      }
    }

    w->znr--;
    cnt++;
  }

  chk_updown (w);

  return cnt;
}

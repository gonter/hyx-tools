/*
 *  FILE %ned/01/ned0103.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 01 31: Revision
 *  latest update: 1997-09-14  9:55:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int ned_vertical_scroll_count;

/* ------------------------------------------------------------------------ */
int ned_w_cursor_down (
register struct WINDOWCTRL *w,
int num)
{
  register struct LINE *l;
  int cnt= 0;

  for (; num > 0; num--)
  {
#ifdef USE_TK
    tk_resetcup ();
#endif

    if ((l= w->WC_act) == (struct LINE *) 0) break;

    if (l->next == (struct LINE *) 0)
    {
      ned_show_display_range (w);
      return 0;
    }

    if (w->cy < w->by)
    {
      w->cy++;
      w->WC_act= l= l->next;
    }
    else
    {
      if (ned_vertical_scroll_count <= 1)
      {
        w->WC_act= l= l->next;
        w->first= w->first->next;
        wd_upscr (w);
      }
      else
      {
        ned_w_page_down (w, 0);
        l= w->WC_act;
      }
    }

    w->znr++;
    cnt++;
  }

  chk_updown (w);

  return cnt;
}

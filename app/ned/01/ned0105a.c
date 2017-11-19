/*
 *  FILE %ned/01/ned0105a.c
 *
 *  move cursor one position to the right
 *  see also: %ned/01/ned0106a.c
 *
 *  written:       1995-01-01: extracted from %ned/01/ned0105a.c
 *  latest update: 1996-07-26  2:44:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>
#include <gg/keys.h>

extern int ned_horizontal_scroll_count;

/* ------------------------------------------------------------------------ */
int ned_q_cursor_left (struct WINDOWCTRL *w, int df)
{
  struct FEATURE **fp;

  if (w->cx > w->ax) w->cx--;
  else
  {
    if (ned_horizontal_scroll_count <= 1)
    { /* scroll horizontally */
      w->hv--;
      if (df)
      {
        w_scrblk_right (w->page, w->ax, w->ay, w->bx, w->by, WV_GELB, 1);
#ifdef TEST /* 1995-10-29 */
        wd_coldis (w, w->ay, w->by, w->first, w->cx+w->hv-w->ax, w->ax);
#endif
        wd_2setup (w, w->ax, w->ay, w->ax, w->by);
      }
    }
    else
    { /* jump scroll horizontally */
      int sc= ned_horizontal_scroll_count;
      if (sc > w->hv) sc= w->hv;
      w->hv -= sc;
      w->cx += sc-1;

      if (df) ned_display_window (w);
    }
  }

  /* EXP: 1996-03-10 13:13:58 */
  if ((fp= ned_feature_find2 (w, 1)) != (struct FEATURE **) 0)
    show_feature (*fp);

  return 0;
}

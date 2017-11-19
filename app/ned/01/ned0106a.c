/*
 *  FILE %ned/01/ned0106a.c
 *
 *  move cursor one position to the right
 *  see also: %ned/01/ned0105a.c
 *
 *  written:       1995-01-01: extracted from %ned/01/ned0106.c
 *                 1991 05 30: Revision
 *                 1991 09 15: Revision
 *  latest update: 1996-08-27 21:58:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;
extern int ned_horizontal_scroll_count;

/* ------------------------------------------------------------------------ */
int ned_q_cursor_right (struct WINDOWCTRL *w, int df)
{
  struct FEATURE **fp;

  if (w->cx < w->bx) w->cx++;
  else
  {
    if (ned_horizontal_scroll_count <= 1)
    { /* scroll horizontally */    
      w->hv++;

      if (df)
      {
        w_scrblk_left (akt_page, w->ax, w->ay, w->bx, w->by, WV_GELB, 1);
        wd_2setup (w, w->bx, w->ay, w->bx, w->by);
      }
    }
    else
    { /* jump scroll horizontally */
      w->hv += ned_horizontal_scroll_count;
      w->cx -= ned_horizontal_scroll_count-1;

      if (df) ned_display_window (w);
    }
  }

  /* EXP: 1996-03-10 13:13:58 */
  if ((fp= ned_feature_find2 (w, 1)) != (struct FEATURE **) 0)
    show_feature (*fp);

  return 0;
}

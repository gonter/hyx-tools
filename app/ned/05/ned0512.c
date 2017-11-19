/*
 *  FILE %ned/05/ned0512.c
 *
 *  elementare Editierfunktionen: TAB
 *
 *  written:       1987 04 08
 *                 1990 05 20: Revision
 *                 1991 02 07: Revision
 *                 1991 09 15: Revision
 *                 1995-10-29: use horizontal scrolling more efficiently
 *  latest update: 1998-08-19 18:43:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

#define SPECIAL_TAB 76
extern int akt_page;
extern int ned_tabstop;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void tabulate ()
{
  int i;
  int j;
  int ins;
  int pos;

#ifdef USE_ABBREVIATIONS
  ned_check_abbrev ();
#endif /* USE_ABBREVIATIONS */

  ins= aw->ins_flg;
  if (aw->file_format == FMT_BINARY)
  {
    ned_wc_insert (aw, '\t', 0);
    j= 1;
  }
  else
  {
    pos= aw->hv + aw->cx - aw->ax;
    j= ned_tabstop - (pos % ned_tabstop);
    if (pos < SPECIAL_TAB
        && pos + j >= SPECIAL_TAB)
      j= SPECIAL_TAB-pos;                      /* special TAB position     */
    aw->ins_flg= INSFLG_insert;                /* TABs always insert (???) */
    for (i= 0; i < j; i++) ned_wc_insert (aw, ' ', 0);
  }

  aw->f_upd= 1;

  if ((aw->cx+j) < aw->bx)
  {
    aw->cx += j;
    wd_displine (aw, aw->WC_act, aw->cy, aw->ax, aw->bx);
  }
  else
  {
#ifdef MSDOS
#define VERSION_2       /* 1995-10-29: everything else is OBSOLETE, I think */
#else
#define VERSION_1       /* save bet; T2D @@@ TK with horizontal scroll?     */
#endif

#ifdef VERSION_1        /* geht z.Z. nicht besser :((                       */
    aw->hv += j;        /* horiz. Scroll ######                             */
                        /* besser so, weil multicolumn horizontal scroll    */
                        /* benoetigt wird, um das scrolling effizient zu    */
                        /* implementieren.                                  */
                        /* dieser Abschnitt war vor 1995-10-29 verwendet    */
    ned_display_window (aw);
#endif /* VERSION_1 */

#ifdef VERSION_2        /* 1995-10-29: efficient horizontal scroll          */
    wd_displine (aw, aw->WC_act, aw->cy, aw->bx-j-1, aw->bx);
    w_scrblk_left (akt_page, aw->ax, aw->ay, aw->bx, aw->by, WV_GELB, j);
    aw->hv += j;
    wd_2setup (aw, aw->bx-j, aw->ay, aw->bx, aw->by);
    /* NOTE: when ned_q_cursor_right() uses a scroll count parameter, this  */
    /*       should be used as that would be more efficient code.           */
#endif /* VERSION_2 */

#ifdef VERSION_3        /* 1995-10-29: inefficient horizontal scroll        */
    /* NOTE: (1995-10-29) multi column scrolls 2b implemented */
    wd_displine (aw, aw->WC_act, aw->cy, aw->bx-1, aw->bx);
    for (i= 0; i < j; i++) ned_q_cursor_right (aw, 1);
#endif /* VERSION_3 */
  }

  /**** wd_displine (aw, aw->WC_act, aw->cy, aw->ax, aw->bx); 1995-10-29 ****/
  aw->ins_flg= ins;
}

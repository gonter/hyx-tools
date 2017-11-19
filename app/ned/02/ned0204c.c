/*
 *  FILE %ned/02/ned0204c.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1996-05-26 extracted from ned0204.c
 *  latest update: 1997-10-26  9:18:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int COL_WIN_NUM;
#ifdef MSDOS
extern struct WINDOWCTRL *aw;
extern int akt_page;
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
void ned_decorate_window (struct WINDOWCTRL *w)
{
  int wp;
  int wi;                       /* Window Index (Nummer des Windows)        */

  if (w == (struct WINDOWCTRL *) 0) return;

  wi= w->wc_window_number;

#ifdef MSDOS
  if ((wp= w->page) != akt_page) w_selpage (wp= akt_page= aw->page);
#else
  wp= 0;
#endif

#ifndef USE_TK
  if ((w->w_upd & 0x04) && w->box_type)
  {
    w_disp_box (wp, w->ax-1, w->ay-1, w->bx+1, w->by+1,
                w->attr_box, w->box_type, 0x00FA);
    if (w->box_type == BOX_TYPE_single
        || w->box_type == BOX_TYPE_double)
      wd_show_wdnr (wp, w->ax, w->ay-1, COL_WIN_NUM, wi);
    /*** w_setcup (wp, 0, 0); ???? 1996-05-26 18:45:37 */
  }
#else
  wd_show_wdnr (wp, w->ax, w->ay-1, COL_WIN_NUM, wi);
#endif

  window_status (w);            /* show window status line                  */
  ned_show_display_range (w);   /* show the window range within the file    */
  show_buttons (w);             /* also display the buttons                 */
}

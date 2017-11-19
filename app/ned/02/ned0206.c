/*
 *  FILE %ned/02/ned0206.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1996-05-26 22:46:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *windows;
extern struct WINDOWCTRL *aw;
extern int akt_page;

/* ------------------------------------------------------------------------ */
void wda_setup ()
{
  int wi= 1;
  register struct WINDOWCTRL *w;
  int xax, xay, xbx, xby;

  xax= aw->ax; xay= aw->ay;
  xbx= aw->bx; xby= aw->by;

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
  {
    w->wc_window_number= wi++;

    if (w->page == akt_page
        && w != aw
        && (w->ax < xax || w->ay < xay          /* nur sichtbare Windows    */
            || w->bx > xbx || w->by > xby       /* werden neu aufgebaut!    */
           )
       )
    {
      if (w->w_upd & 0x02)
      {
        /**** ned_jmp_2line_by_nr (w, w->znr, 0x00); 1996-05-26 22:44:34 ****/
        ned_w_jmp_aktline (w, NEDJMP_LINE_3, 0, 0x00);
      }
      w->w_upd |= 0x05;
      ned_display_window (w);
    }
  }

  if (aw->w_upd & 0x02)
  {
    /***** ned_jmp_2line_by_nr (aw, aw->znr, 0x00); 1996-05-26 22:45:56 */
    ned_w_jmp_aktline (aw, NEDJMP_LINE_3, 0, 0x00);
  }
  aw->w_upd |= 0x05;
  ned_display_window (aw);
}

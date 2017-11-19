/*
 *  FILE %ned/09/ned0933.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1997-06-13 13:18:32
 *
 */

#include <tk.h>
#include <tcl.h>

#include <syslog.h>
#include <stdio.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tk_redraw_window (NED_Widget *nw, int pxa, int pya, int pxb, int pyb)
{
  struct WINDOWCTRL *w;
  int cya;

#ifdef DEBUG
  int cxa= ned_get_cx_pos (nw, pxa);
      cya= ned_get_cy_pos (nw, pya);
  int cxb= ned_get_cx_pos (nw, pxb);
  int cyb= ned_get_cy_pos (nw, pyb);

printf ("ned0933.c: nw=0x%08lX pxa=%d char_width=%d line_height=%d\n",
 nw, pxa, nw->char_width, nw->line_height);

  printf ("cxa=%d cya=%d cxb=%d cyb=%d\n", cxa, cya, cxb, cyb);
#endif

  XFillRectangle (nw->display, Tk_WindowId (nw->tkwin), nw->cursedTextGC,
                  pxa, pya, pxb-pxa, pyb-pya);

  w= nw->ned_window;
  wd_2setup (w, ned_get_cx_pos (nw, pxa), cya= ned_get_cy_pos (nw, pya),
                ned_get_cx_pos (nw, pxb),      ned_get_cy_pos (nw, pyb));

  if (cya <= 2) ned_decorate_window (w);

  setcup (w);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tk_redraw_window2 (struct WINDOWCTRL *w)
{
  NED_Widget *nw;

  if ((nw= (NED_Widget *) w->wc_widget) == (NED_Widget *) 0) return -1;

  return ned_tk_redraw_window (nw, 0, 0, nw->num_x_pixels, nw->num_y_pixels);
}

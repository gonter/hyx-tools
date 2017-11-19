/*
 *  FILE %ned/unix/tk2_scr.c
 *
 *  written:       1996-07-11 [extracted from tk2.c]
 *  latest update: 1996-08-08 19:57:25
 *  $Id: tk2_scr.c,v 1.3 2005/06/14 02:36:07 gonter Exp $
 *
 */

#include "ed.h"
#include <tcl.h>
#include <tk.h>
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"
/* see <gg/window.h> */

/* @@@ T2D ###: needs NED */
extern struct WINDOWCTRL *aw;

/* ----- SCROLLING -------------------------------------------------------- */
static GC scrollGC;
static int scrollGC_initialized= 0;

GC get_scrollGC ()
{
  XGCValues gcValues;
  Tk_Window tkwin;
  NED_Widget *nw;

  if (scrollGC_initialized) return scrollGC;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return;

  tkwin= nw->tkwin;

  gcValues.graphics_exposures= True;
  scrollGC= Tk_GetGC (tkwin, GCGraphicsExposures, &gcValues);

  return scrollGC;
}

/* ------------------------------------------------------------------------ */
int _tk_scrblk (int ax, int ay, int bx, int by, int dir, int cnt)
{
  GC scGC;
  NED_Widget *nw;
  Tk_Window tkwin;
  Drawable da;
  Display *dpy;
  int x_pos;
  int y_pos;
  int x_pos2;
  int y_pos2;
  int width;
  int height;

  if ((scGC= get_scrollGC ()) == (GC) 0) return -1;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return -1;

  tkwin= nw->tkwin;
  da= (Drawable) Tk_WindowId (tkwin);
  dpy= nw->display;

  switch (dir)
  {
    case 1: /* down */
      x_pos= x_pos2= ax * nw->char_width;
      width= (bx - ax + 1) * nw->char_width;

      y_pos= ay * nw->line_height;
      y_pos2= (ay + cnt) * nw->line_height;
      height= (by - ay - cnt + 1) * nw->line_height;
      break;

    case 2: /* up */
      x_pos= x_pos2= ax * nw->char_width;
      width= (bx - ax + 1) * nw->char_width;

      y_pos= (ay + cnt) * nw->line_height;
      y_pos2= ay * nw->line_height;
      height= (by - ay - cnt + 1) * nw->line_height;
      break;

    case 3: /* left */
      x_pos= (ax + cnt) * nw->char_width;
      x_pos2= ax * nw->char_width;
      width= (bx - ax - cnt + 1) * nw->char_width;

      y_pos= ay * nw->line_height;
      y_pos2= ay * nw->line_height;
      height= (by - ay + 1) * nw->line_height;
      break;

    case 4: /* right */
      x_pos= ax * nw->char_width;
      x_pos2= (ax + cnt) * nw->char_width;
      width= (bx - ax - cnt + 1) * nw->char_width;

      y_pos= ay * nw->line_height;
      y_pos2= ay * nw->line_height;
      height= (by - ay + 1) * nw->line_height;
      break;

    default: return -1;
  }

  XCopyArea (dpy, da, da, scGC,
             x_pos, y_pos,
             width, height,
             x_pos2, y_pos2);

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_scrblk_down (int ax, int ay, int bx, int by, int attr, int cnt)
{
  if (_tk_scrblk (ax, ay, bx, by, 1, cnt) != 0) p_refresh ();
  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_scrblk_up (int ax, int ay, int bx, int by, int attr, int cnt)
{
  if (_tk_scrblk (ax, ay, bx, by, 2, cnt) != 0) p_refresh ();
  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_scrblk_left (int page, int ax, int ay, int bx, int by, int attr, int cnt)
{
  if (_tk_scrblk (ax, ay, bx, by, 3, cnt) != 0) p_refresh ();
  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_scrblk_right (int page, int ax, int ay, int bx, int by, int attr, int cnt)
{
  if (_tk_scrblk (ax, ay, bx, by, 4, cnt) != 0) p_refresh ();
  return 0;
}

/* ------------------------------------------------------------------------ */
void tk_sig_winch (void)
{
  /* dummy; this should not happen at all */
  tk_bell ();
}

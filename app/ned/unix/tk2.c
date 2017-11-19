/*
 *  FILE %ned/unix/tk2.c
 *
 *  written:       1995-09-30
 *  latest update: 2000-08-24 13:12:39
 *  $Id: tk2.c,v 1.3 2007/04/13 10:15:28 gonter Exp $
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

/* ------------------------------------------------------------------------ */
GC ned_tk_get_GC (NED_Widget *nw, int a)
{
  GC x;
  int i;

  switch (a)
  {
    case NED_TK_GC_cursedText:  return nw->cursedTextGC;
    case NED_TK_GC_StatusLine:  return nw->StatusLineGC;
    case NED_TK_GC_markedText:  return nw->markedTextGC;
    case NED_TK_GC_normalText:  return nw->normalTextGC;

    default:
      for (i= nw->attrib_cnt-1; i >= 0; i--)
      {
        if (nw->attrib_num [i] == a) return nw->attrib_GC [i];
      }

      if ((x= ned_tk_setup_GC (nw, a)) != (GC) 0) return x;

      return nw->normalTextGC;
  }
}

/* ------------------------------------------------------------------------ */
int tk_setchar (int p, int x, int y, int a, int c)
{
  NED_Widget *nw;
  Tk_Window tkwin;
  Drawable da;
  GC gc;
  char b[2];

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return 0;

  tkwin= nw->tkwin;
  gc= ned_tk_get_GC (nw, a);
  da= (Drawable) Tk_WindowId (tkwin);

  if (c < 0 || c > 255) c= 0x20; /* otherwise a &yuml; character is displayed in X11 */
  b[0]= c;

  XDrawImageString (nw->display, da, gc,
                    ned_get_x_pos(nw,x), ned_get_y_pos(nw,y),
                    b, 1);

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_setnchar (int p, int x, int y, int a, int c, int cnt)
{
  NED_Widget *nw;
  Tk_Window tkwin;
  Drawable da;
  GC gc;
  char b[2];

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return 0;

  tkwin= nw->tkwin;
  gc= ned_tk_get_GC (nw, a);
  da= (Drawable) Tk_WindowId (tkwin);

  b[0]= c;

  while (cnt-- > 0)
    XDrawImageString (nw->display, da, gc,
                      ned_get_x_pos(nw,x), ned_get_y_pos(nw,y),
                      b, 1);

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_prntcol (int p, int x, int y, int a, char *s)
{
  NED_Widget *nw;
  Tk_Window tkwin;
  Drawable da;
  GC gc;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return 0;

  tkwin= nw->tkwin;
  gc= ned_tk_get_GC (nw, a);
  da= (Drawable) Tk_WindowId (tkwin);

  XDrawImageString (nw->display, da, gc,
                    ned_get_x_pos(nw,x), ned_get_y_pos(nw,y),
                    s, strlen (s));

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_draw_string (
struct WINDOWCTRL *w,
int what,
int x, int y, char *s)
{
  NED_Widget *nw;
  GC gc;
  Tk_Window tkwin;
  Drawable da;

  if (w == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) w->wc_widget) == (NED_Widget *) 0
     ) return 0;

  tkwin= nw->tkwin;
  da= (Drawable) Tk_WindowId (tkwin);

  gc= ned_tk_get_GC (nw, what);

  XDrawImageString (nw->display, da, gc,
                    ned_get_x_pos(nw,x), ned_get_y_pos(nw,y),
                    s, strlen (s));

  return 0;
}

/* ------------------------------------------------------------------------ */
static int last_x= -1, last_y= -1, last_c;
int tk_resetcup ()
{
  if (last_x != -1 && last_y != -1)
  {
    /* tk_setchar (p, last_x, last_y, 0, last_c); 1995-10-27 */
    wd_2setup (aw, last_x, last_y, last_x, last_y);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_setcup (int p, int x, int y)
{
  int c;

  c= get_txt (aw->WC_act, aw->cx - aw->ax + aw->hv);
  tk_setchar (p, x, y, 0x0100, c);

  last_x= x;
  last_y= y;
  last_c= c;

  return 0;
}

/* ------------------------------------------------------------------------ */
int tk_init () { return 0; }
int tk_cls () { return 0; }

/* ------------------------------------------------------------------------ */
void tk_bell ()
{
  NED_Widget *nw;

  if (aw == (struct WINDOWCTRL *) 0) return;
  if ((nw= (NED_Widget *) aw->wc_widget) != (NED_Widget *) 0)
    XBell (nw->display, 0);
}

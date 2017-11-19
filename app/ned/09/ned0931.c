/*
 *  FILE %ned/09/ned0931.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1999-07-17 17:18:05
 *
 */


#include <tk.h>
#include <tcl.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_tk_event_procedure (ClientData clientData, XEvent *eventPtr)
{
  NED_Widget *nw;

  if ((nw= (NED_Widget *) clientData) == (NED_Widget *) 0) return;
  aw= nw->ned_window; /* active window changes */

  if (eventPtr->type == KeyPress)
  {
    NED_tk_key_pressed (clientData, eventPtr);
    return;
  }

  if (eventPtr->type == MapNotify)
  {
    ned_tk_redraw_window (nw, 0, 0, nw->num_x_pixels, nw->num_y_pixels);
    return;
  }

  if (eventPtr->type == DestroyNotify)
  {
    p_ssave ();                 /* save on close or setup... */
    return;
  }

  if (eventPtr->type == Expose)
  {
    int pxa, pya, pxb, pyb;

    pxa= eventPtr->xexpose.x;
    pya= eventPtr->xexpose.y;
    pxb= eventPtr->xexpose.width + pxa;
    pyb= eventPtr->xexpose.height + pya;

    ned_tk_redraw_window (nw, pxa, pya, pxb, pyb);
    return;
  }

  if (eventPtr->type == FocusIn)
  {
    setcup (aw); /* not even that should be necessary ... */
    return;
  }

  if (eventPtr->type == ConfigureNotify)
  {
    nw->num_x_pixels= eventPtr->xconfigure.width;
    nw->num_y_pixels= eventPtr->xconfigure.height;
    aw->bx= ((nw->num_x_pixels - nw->num_x_pix_offset - nw->num_x_pix_extra)
            / nw->char_width) -1;
    aw->by= ((nw->num_y_pixels - nw->num_y_pix_offset - nw->num_y_pix_extra)
            / nw->line_height) -1;

    ned_tk_set_geometry (nw);
    ned_tk_redraw_window (nw, 0, 0, nw->num_x_pixels, nw->num_y_pixels);
    return;
  }

  if (eventPtr->type == MotionNotify
      || eventPtr->type == ButtonPress
      || eventPtr->type == ButtonRelease
     )
  {
    int t= 0;
    int x, y;
    int st;

    if (eventPtr->type == MotionNotify)
    {
      st= eventPtr->xmotion.state;
      x= eventPtr->xmotion.x;
      y= eventPtr->xmotion.y;
    }
    else
    {
      st= eventPtr->xbutton.state;
      x= eventPtr->xbutton.x;
      y= eventPtr->xbutton.y;
    }

    if (st & Button1Mask) t |= 1;
    if (st & Button2Mask) t |= 4;
    if (st & Button3Mask) t |= 2;

    ned_mouse_event (ned_get_cx_pos (nw, x), ned_get_cy_pos (nw, y), t,
                     eventPtr->xbutton.x_root, eventPtr->xbutton.y_root);

    return;
  }
}

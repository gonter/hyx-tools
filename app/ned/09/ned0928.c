/*
 *  FILE %ned/09/ned0928.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1997-10-26 10:48:40
 *
 */

#include <tk.h>
#include <tcl.h>

#include <syslog.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int _ned_tk_destroy_widget (NED_Widget *nw)
{
  Tk_Window tkwin;
  Display *disp;
  int i;

  if (nw == (NED_Widget *) 0
      || (tkwin= nw->tkwin) == (Tk_Window) 0
      || (disp= nw->display) == (Display *) 0
     ) return -1;

  /* #### T2D @@@: Delete NED Widget, incomplete!! */
  Tk_FreeGC (disp, nw->normalTextGC);
  Tk_FreeGC (disp, nw->cursedTextGC);
  Tk_FreeGC (disp, nw->StatusLineGC);
  Tk_FreeGC (disp, nw->markedTextGC);
  Tk_FreeGC (disp, nw->selectedTextGC);

  for (i= nw->attrib_cnt-1; i >= 0; i--)
  {
    Tk_FreeGC (disp, nw->attrib_GC [i]);
  }
  nw->attrib_cnt= 0;

  Tk_DeleteEventHandler (tkwin, NED_WIDGET_EVENT_MASK,
                         ned_tk_event_procedure, (ClientData) nw);

  Tk_DestroyWindow (tkwin);

  /* T2D: destroy nw too ! (1996-07-21 16:37:28) */

  return TCL_OK;
}

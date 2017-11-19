/*
 *  FILE %ned/09/ned0934.c
 *
 *  NED's tk widget stuff
 *  handle the export of the selection
 *
 *  written:       1995-11-08
 *  latest update: 1998-08-16 12:33:16
 *  $Id: ned0934.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <string.h>
#include <tk.h>
#include <tcl.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"
#include <X11/Xatom.h>

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tk_exp_selection_procedure (
ClientData clientData,
int offset,
char *buffer,
int maxBytes)
{
  NED_Widget *nw;

  /* NOTE: 1997-06-14 19:22:17: handling of offset/maxBytes seems to work */

  ned_message_1 ("selection activated A");
  if ((nw= (NED_Widget *) clientData) == (NED_Widget *) 0
      || ned_block_2_string (buffer,
           maxBytes+1,    /* there is extra space for the 0-char */
           (long) offset,
           0x0001) == (char *) 0
     ) return -1;

  ned_message_1 ("selection activated B");

  return strlen (buffer);
}

/* ------------------------------------------------------------------------ */
void ned_tk_lost_selection (ClientData cd)
{
  NED_Widget *nw;

  if ((nw= (NED_Widget *) cd) != (NED_Widget *) 0) /* ??? ****/
  {
    nw->selection_active= 0;
    ned_display_window (nw->ned_window);
  }
}

/* ------------------------------------------------------------------------ */
int ned_tk_block_export_flag (int flag)
{
  NED_Widget *nw;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return -1;

  switch (flag)
  {
    case 0:
      nw->selection_active= 0;
      Tk_ClearSelection (nw->tkwin, XA_PRIMARY);
      return 0;

    case 1:
      nw->selection_active= 1;
      Tk_OwnSelection (nw->tkwin, XA_PRIMARY, ned_tk_lost_selection,
                       (ClientData) nw);
      return 0;

    default:
      return -1;
  }
}

/* ------------------------------------------------------------------------ */
void ned_tk_claim_selection ()
{
  ned_tk_block_export_flag (1);
}

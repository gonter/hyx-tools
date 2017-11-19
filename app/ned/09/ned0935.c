/*
 *  FILE %ned/09/ned0935.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-11-08
 *  latest update: 1997-10-26 10:23:56
 *
 */

#include <tk.h>
#include <tcl.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tk_imp_selection_procedure (
ClientData clientData,
Tcl_Interp *interp,
char *buffer)
{
  NED_Widget *nw;

  if ((nw= (NED_Widget *) clientData) == (NED_Widget *) 0
      || ned_paste_string (buffer, 0, (char *) 0, (char *) 0) == -1
     ) return TCL_ERROR;

  return TCL_OK;
}

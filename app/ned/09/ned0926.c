/*
 *  FILE %ned/09/ned0926.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1997-10-26 10:24:05
 *  $Id: ned0926.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tk.h>
#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tk_create_widget (
ClientData clientData,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  return _ned_tk_create_widget (clientData, interp, argc, argv,
                                (struct WINDOWCTRL *) 0 /* ###### */);
}

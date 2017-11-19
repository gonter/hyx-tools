/*
 *  FILE %ned/09/ned0946.c
 *
 *  set a marker
 *
 *  set_marker <str>
 *
 *  written:       1996-10-03
 *  latest update: 1997-06-28 22:50:18
 *  $Id: ned0946.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tcl_set_marker (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 1)
  {
    interp->result= "no string given";
    return TCL_ERROR;
  }

  ned_set_marker (aw, argv [1][0]);

  return TCL_OK;
}

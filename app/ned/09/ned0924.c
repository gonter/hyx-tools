/*
 *  FILE %ned/09/ned0924.c
 *
 *  NED's tcl application initialization
 *
 *  written:       1995-01-08
 *  latest update: 1997-10-26 10:24:11
 *  $Id: ned0924.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_execute_primitive (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  ned_primitive *ned_primitive_func;

#ifdef MSDOS
  argv;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (client_data == (ClientData) 0)
  {
    interp->result= "invalid NED function";
    return TCL_ERROR;
  }

  if (argc != 1) /* argc: 0 .. n-1 */
  {
    interp->result= "wrong # args";
    return TCL_ERROR;
  }

  ned_primitive_func= (ned_primitive *) client_data;

  (*ned_primitive_func) ();

  return TCL_OK;
}

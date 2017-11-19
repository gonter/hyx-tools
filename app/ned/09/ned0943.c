/*
 *  FILE %ned/09/ned0943.c
 *
 *  enter an entity
 *
 *  enter_entity <str>
 *
 *  written:       1996-06-09
 *  latest update: 1996-07-14 10:43:51
 *  $Id: ned0943.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_enter_entity (
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

  ned_enter_entity (argv [1]);

  return TCL_OK;
}

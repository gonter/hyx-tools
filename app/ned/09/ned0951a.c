/*
 *  FILE %ned/09/ned0951a.c
 *
 *  define_abbrev <lhs> <rhs>
 *
 *  written:       1997-02-08
 *  latest update: 1997-02-08 21:56:29
 *  $Id: ned0951a.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <stdio.h>
#include <gg/dpp.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_def_abbrev (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 2)
  {
    interp->result= "not enough parameters";
    return TCL_ERROR;
  }

  ned_define_abbrev (argv [1], argv [2]);

  return TCL_OK;
}

/*
 *  FILE %ned/09/ned0945.c
 *
 *  evaluate a tag
 *
 *  tag <str>
 *
 *  written:       1996-08-04
 *  latest update: 1996-08-04 20:32:33
 *  $Id: ned0945.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_eval_tag (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 1)
  {
    interp->result= "no string given";
    return TCL_ERROR;
  }

  for (i= 1; i < argc; i++) ex_tag_command (argv [i]);

  return TCL_OK;
}

/*
 *  FILE %ned/09/ned0944.c
 *
 *  directly jump to a specified line
 *
 *  jump_to_line <num>
 *
 *  written:       1996-07-14
 *  latest update: 1996-07-14 10:43:51
 *  $Id: ned0944.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tcl_jump_to_line (
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
    interp->result= "no line specified";
    return TCL_ERROR;
  }

  ned_cb_jump_to_line (argv [1], (void *) aw);

  return TCL_OK;
}

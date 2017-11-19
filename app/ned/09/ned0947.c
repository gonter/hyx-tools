/*
 *  FILE %ned/09/ned0947.c
 *
 *  set_marker [-begin|-boln] <str>
 *
 *  jump to named marker,
 *  if -begin is specified, jump to the first character at the
 *      begin of the line, not to the marker position itself
 *  if -boln is specified, jump to the begin of the line (column 0),
 *      not to the marker position itself
 *
 *  written:       1996-10-03
 *  latest update: 1996-10-03 10:52:09
 *  $Id: ned0947.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#include <tcl.h>

#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_jmp_marker (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  const char *marker_name= (char *) 0;
  const char *arg;
  int boln= 0;
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

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (abbrev ("-begin", arg, 2)) boln= 1;
    else if (abbrev ("-boln", arg, 2)) boln= 2;
    else if (marker_name != (char *) 0) marker_name= arg;
  }

  ned_jmp_marker (marker_name [0], boln);

  return TCL_OK;
}

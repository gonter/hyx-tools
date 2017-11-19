/*
 *  FILE %ned/09/ned0949.c
 *
 *  store something in the feature cache
 *
 *  define_feature <name> <type> <str>
 *
 *  written:       1996-11-03
 *  latest update: 1996-11-10 13:32:23
 *  $Id: ned0949.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <stdio.h>
#include <gg/dpp.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_define_feature (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 3)
  {
    interp->result= "not enough parameters";
    return TCL_ERROR;
  }

  ned_store_feature_cache (PAR (token, argv [1]),
                           PAR (feature_string, argv [3]),
                           PAR (feature_type, argv [2]));

  return TCL_OK;
}

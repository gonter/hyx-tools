/*
 *  FILE %ned/09/ned0940.c
 *
 *  place a markup around a block
 *
 *  set_markup <str>
 *
 *  written:       1996-05-07
 *  latest update: 1997-10-26 10:23:19
 *  $Id: ned0940.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tcl_set_markup (
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
    interp->result= "no tag given";
    return TCL_ERROR;
  }

  if (ned_markup_block_2 (aw, argv [1]) != 0)
  {
    interp->result= "invalid tag given";
    return TCL_ERROR;
  }

  return TCL_OK;
}

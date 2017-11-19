/*
 *  FILE %ned/09/ned0937b.c
 *
 *  edit a cross reference frame
 *
 *  edit_crf keyword+
 *
 *  written:       1996-03-17
 *  latest update: 1997-10-26 10:23:35
 *  $Id: ned0937b.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_edit_crf (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  const char *arg;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  for (i= 1; i < argc; i++)
  {
    if ((arg= argv [i]) == (char *) 0) continue;

    ned_cross_ref (arg, 0, CRF_IN_CRF, CRF_GLOBAL_AND_LOCAL, 1);
  }

  return TCL_OK;
}

/*
 *  FILE %ds/tcl/tcl_0000.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-17 20:22:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_template (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  int i;
  int rc= TCL_OK;
  char *arg;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];
  }

  return rc;
}

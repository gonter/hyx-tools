/*
 *  FILE %ds/tcl/tcl_0008.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-18
 *  latest update: 1996-03-18  8:07:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <tcl.h>
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_set_dirinf (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 2)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if (fvf_set_dirinf (argv [1]) != 0)
  {
    interp->result= "invalid argument";
    return TCL_ERROR;
  }

  return TCL_OK;
}

/*
 *  FILE %ds/tcl/tcl_0004.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-17 21:04:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_virtual_filename (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
#define VP_SIZE 1024
  char vp [VP_SIZE];

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 2)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if (find_logic_filename (argv [1], vp, VP_SIZE) != 1)
    interp->result= (char *) 0; /* TEST: does that work?? */
  else Tcl_SetResult (interp, vp, TCL_VOLATILE);

  return TCL_OK;
}

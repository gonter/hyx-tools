/*
 *  FILE %ds/tcl/tcl_0005.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-17 21:17:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_real_filename (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  char *r_fnm;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 2 && argc != 3)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if ((r_fnm= real_filename (argv [1], (argc == 3) ? argv [2] : (char *) 0))
      == (char *) 0)
  {
    interp->result= "invalid argument";
    return TCL_ERROR;
  }

  Tcl_SetResult (interp, r_fnm, TCL_DYNAMIC);

  return TCL_OK;
}

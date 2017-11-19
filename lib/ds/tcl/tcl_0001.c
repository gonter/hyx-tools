/*
 *  FILE %ds/tcl/tcl_0001.c
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
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_translate_virtual_name (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  char *fnm= (char *) 0;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 2)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if ((fnm= translate_logic_filename (argv [1])) == (char *) 0)
  {
    interp->result= "invalid argument";
    return TCL_ERROR;
  }

  Tcl_SetResult (interp, fnm, TCL_DYNAMIC);

  return TCL_OK;
}

/*
 *  FILE %ds/tcl/tcl_0003.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-17 20:59:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_define_virtual_path (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIRTUAL_FILENAME *a;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 3)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if ((a= _define_logic_filename (argv [1], argv [2]))
      == (struct VIRTUAL_FILENAME *) 0)
  {
    interp->result= "invalid argument";
    return TCL_ERROR;
  }

  return TCL_OK;
}

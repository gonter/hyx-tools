/*
 *  FILE %ds/tcl/tcl_0006.c
 *
 *  Tcl subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-18 13:58:05
 *  $Id: tcl_0006.c,v 1.3 2012/08/10 14:44:09 gonter Exp $
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
int ggtcl_filename_definition (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  char *fnm_elements [2];

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 2 && argc != 3)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  if (filename_definition (argv [1],
                                &fnm_elements [0],
                                &fnm_elements [1],
                                (argc == 3) ? argv [2] : (char *) 0)
      != 0)
  {
    interp->result= "invalid argument";
    return TCL_ERROR;
  }

  Tcl_SetResult (interp, Tcl_Merge (2, fnm_elements), TCL_DYNAMIC);

  return TCL_OK;
}

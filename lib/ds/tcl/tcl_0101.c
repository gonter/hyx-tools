/*
 *  FILE %ds/tcl/tcl_0101.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-09-28
 *  latest update: 1996-11-10 17:17:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <tcl.h>
#include <gg/hyx.h>
#include <gg/dpp.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_hyx_set_color_code (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc != 3)
  {
    interp->result= "wrong number of args";
    return TCL_ERROR;
  }

  hyx_set_color_code (argv [1], get_parameter_value (argv [2]));

  return TCL_OK;
}

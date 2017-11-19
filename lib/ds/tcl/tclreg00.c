/*
 *  FILE %ds/tcl/tclreg00.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-09-28
 *  latest update: 1996-09-28 11:30:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
int ggtcl_reg_services (Tcl_Interp *interp, struct N2P *service_table)
{
  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  for (;; service_table++)
  {
    if (service_table->cmd == (char *) 0) break;

    Tcl_CreateCommand (interp, service_table->cmd, service_table->prc,
                       (ClientData) 0,
                       (Tcl_CmdDeleteProc *) 0);
  }

  return TCL_OK;
}

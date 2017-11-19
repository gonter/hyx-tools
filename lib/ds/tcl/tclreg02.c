/*
 *  FILE %ds/tcl/tclreg02.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-09-28
 *  latest update: 1997-12-04 22:16:50
 *  $Id: tclreg02.c,v 1.2 2012/08/10 14:44:09 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
static struct N2P N2P_list [] =
{
  { "hyx_set_color_code",       (Tcl_CmdProc *) ggtcl_hyx_set_color_code } ,

  { (char *) 0,                 (Tcl_CmdProc *) 0 }
} ;

/* ------------------------------------------------------------------------ */
int ggtcl_reg_hyx_services (Tcl_Interp *interp)
{
  return ggtcl_reg_services (interp, N2P_list);
}

/* 
 *  FILE %ds/vieos/vieos.c
 *
 *  written:       1995-12-14
 *  latest update: 1996-03-19  9:19:13
 *
 */

#include <tcl.h>
#include <gg/vieos.h>

/*
 * The following variable is a special hack that is needed in order for
 * Sun shared libraries to be used for Tcl.
 */

extern int matherr ();
int *tclDummyMathPtr= (int *) matherr;

int main (int argc, char *argv [])
{
  Tcl_Main (argc, argv, Tcl_AppInit);
  return 0;
}

/*
 *----------------------------------------------------------------------
 *
 * Tcl_AppInit --
 *
 *  This procedure performs application-specific initialization.
 *  Most applications, especially those that incorporate additional
 *  packages, will have their own version of this procedure.
 *
 * Results:
 *  Returns a standard Tcl completion code, and leaves an error
 *  message in interp->result if an error occurs.
 *
 * Side effects:
 *  Depends on the startup script.
 *
 *----------------------------------------------------------------------
 */

int Tcl_AppInit (Tcl_Interp *interp)    /* Interpreter for application. */
{
  if (Tcl_Init(interp) == TCL_ERROR
      || vieos_create_context (interp, (void *) 0, "vieos")
         == (struct VIEOS_CONTEXT *) 0
      || ggtcl_reg_filename_services (interp) != TCL_OK
     )
    return TCL_ERROR;

  /*
   * Specify a user-specific startup file to invoke if the application
   * is run interactively.  Typically the startup file is "~/.apprc"
   * where "app" is the name of the application.  If this line is deleted
   * then no user-specific startup file will be run under any conditions.
   */

  tcl_RcFileName = "~/.vieosrc";
  return TCL_OK;
}


/*
 *  FILE %ds/vieos/vieosg02.c
 *
 *  execute generic object methods
 *
 *  written:       1995-12-16
 *  latest update: 1996-03-17 19:34:38
 *
 */

#include <string.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_generic_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIEOS_GENERIC *vg;
  char *method;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((vg= (struct VIEOS_GENERIC *) clientData) == (struct VIEOS_GENERIC *) 0
      || vg->VIEG_signature != SIG_VIEOS_GENERIC
     )
  {
    Tcl_SetResult (interp, "unknown object", TCL_STATIC);
    return TCL_ERROR;
  }

  if (argc == 2)
  {
    if ((method= argv [1]) == (char *) 0 || *method == 0) goto ERROR;

    /* BEGIN standard methods - - - - - - - - - - - - - - - */
    if (abbrev ("creator", method, 4))
    {
      struct VIEOS_CONTEXT *vc_up;      /* the creator of this object       */

      interp->result= ((vc_up= (struct VIEOS_CONTEXT *) vg->VIEG_context)
                      == (struct VIEOS_CONTEXT *) 0)
                      ? ""                /* the absolute creator           */
                      : vc_up->VC_name;
        
      return TCL_OK;
    }

    if (abbrev ("class", method, 3))
    {
      Tcl_SetResult (interp, "generic", TCL_STATIC);
      return TCL_OK;
    }

    if (abbrev ("name", method, 3))
    {
      interp->result= vg->VIEG_name;
      return TCL_OK;
    }

    if (strcmp ("destroy", method) == 0)
    {
      Tcl_DeleteCommand (interp, vg->VIEG_name);
      vieos_destroy_generic (vg);

      Tcl_SetResult (interp, "generic destroyed", TCL_STATIC);
      return TCL_OK;
    }
    /* END standard methods - - - - - - - - - - - - - - - */
  }

ERROR:
  Tcl_SetResult (interp, "unknown method", TCL_STATIC);
  return TCL_ERROR;
}

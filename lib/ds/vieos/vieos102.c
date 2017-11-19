/*
 *  FILE %ds/vieos/vieos102.c
 *
 *  execute markup object methods
 *
 *  written:       1995-03-19
 *  latest update: 1996-03-17 23:04:22
 *
 */

#include <string.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_markup_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIEOS_MARKUP *vm;
  char *method;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((vm= (struct VIEOS_MARKUP *) clientData) == (struct VIEOS_MARKUP *) 0
      || vm->VIEM_signature != SIG_VIEOS_MARKUP
     )
  {
    Tcl_SetResult (interp, "unknown object", TCL_STATIC);
    return TCL_ERROR;
  }

  if (argc == 2)
  {
    method= argv [1];

    /* BEGIN standard methods - - - - - - - - - - - - - - - */
    if (abbrev ("creator", method, 4))
    {
      struct VIEOS_CONTEXT *vc_up;      /* the creator of this object       */

      interp->result= ((vc_up= (struct VIEOS_CONTEXT *) vm->VIEM_context)
                      == (struct VIEOS_CONTEXT *) 0)
                      ? ""                /* the absolute creator           */
                      : vc_up->VC_name;
        
      return TCL_OK;
    }

    if (abbrev ("class", method, 3))
    {
      Tcl_SetResult (interp, "markup", TCL_STATIC);
      return TCL_OK;
    }

    if (abbrev ("name", method, 3))
    {
      interp->result= vm->VIEM_name;
      return TCL_OK;
    }

    if (strcmp ("destroy", method) == 0)
    {
      Tcl_DeleteCommand (interp, vm->VIEM_name);
      vieos_destroy_markup (vm);

      Tcl_SetResult (interp, "markup destroyed", TCL_STATIC);
      return TCL_OK;
    }
    /* END standard methods - - - - - - - - - - - - - - - */

    if (strcmp ("dump", method) == 0)
    {
      return TCL_OK;
    }

  }

  Tcl_SetResult (interp, "unknown method", TCL_STATIC);
  return TCL_ERROR;
}

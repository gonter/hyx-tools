/*
 *  FILE %ds/vieos/vieos302.c
 *
 *  execute block object methods
 *
 *  written:       1995-03-19
 *  latest update: 1996-03-17 19:56:55
 *
 */

#include <string.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_block_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIEOS_BLOCK *vb;
  char *method;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((vb= (struct VIEOS_BLOCK *) clientData) == (struct VIEOS_BLOCK *) 0
      || vb->VIEB_signature != SIG_VIEOS_BLOCK
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

      interp->result= ((vc_up= (struct VIEOS_CONTEXT *) vb->VIEB_context)
                      == (struct VIEOS_CONTEXT *) 0)
                      ? ""                /* the absolute creator           */
                      : vc_up->VC_name;
        
      return TCL_OK;
    }

    if (abbrev ("class", method, 3))
    {
      Tcl_SetResult (interp, "block", TCL_STATIC);
      return TCL_OK;
    }

    if (abbrev ("name", method, 3))
    {
      interp->result= vb->VIEB_name;
      return TCL_OK;
    }

    if (strcmp ("destroy", method) == 0)
    {
      Tcl_DeleteCommand (interp, vb->VIEB_name);
      vieos_destroy_block (vb);

      Tcl_SetResult (interp, "block destroyed", TCL_STATIC);
      return TCL_OK;
    }
    /* END standard methods - - - - - - - - - - - - - - - */
  }

ERROR:
  Tcl_SetResult (interp, "unknown method", TCL_STATIC);
  return TCL_ERROR;
}

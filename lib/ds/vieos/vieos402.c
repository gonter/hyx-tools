/*
 *  FILE %ds/vieos/vieos402.c
 *
 *  execute cluster object methods
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:34:56
 *
 */

#include <tcl.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_cluster_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIEOS_CLUSTER *vcl;
  char *method;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((vcl= (struct VIEOS_CLUSTER *) clientData) == (struct VIEOS_CLUSTER *) 0
      || vcl->VCL_signature != SIG_VIEOS_CLUSTER
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

      interp->result= ((vc_up= (struct VIEOS_CONTEXT *) vcl->VCL_context)
                      == (struct VIEOS_CONTEXT *) 0)
                      ? ""                /* the absolute creator           */
                      : vc_up->VC_name;
        
      return TCL_OK;
    }

    if (abbrev ("class", method, 3))
    {
      Tcl_SetResult (interp, "cluster", TCL_STATIC);
      return TCL_OK;
    }

    if (abbrev ("name", method, 3))
    {
      interp->result= vcl->VCL_name;
      return TCL_OK;
    }

    if (strcmp ("destroy", method) == 0)
    {
      Tcl_DeleteCommand (interp, vcl->VCL_name);
      vieos_destroy_cluster (vcl);

      Tcl_SetResult (interp, "cluster destroyed", TCL_STATIC);
      return TCL_OK;
    }
    /* END standard methods - - - - - - - - - - - - - - - */
  }

  if (argc >= 3)
  {
#ifdef __T2D__ /* 1997-01-15 11:36:45 */
    char *fnm_hyx;
    char *fnm_idx;
    char *fnm_lut;
    char *fnm_xfn;
    fnm_hyx= (char *) 0; /* T2D */
#endif /* __T2D__ 1997-01-15 11:36:45 */
  }

ERROR:
  Tcl_SetResult (interp, "unknown method", TCL_STATIC);
  return TCL_ERROR;
}

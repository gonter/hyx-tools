/*
 *  FILE %ds/vieos/vieos002.c
 *
 *  create a new context object
 *
 *  written:       1995-03-19
 *  latest update: 1996-03-18 14:02:32
 *
 */

#include <string.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

char VIEOS_VERSION []= "vieos 1.01.03 $#D1996-03-17 19:37:06";

/* ------------------------------------------------------------------------ */
int vieos_context_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  char *method;
  char *object_name;
  struct VIEOS_CONTEXT *vc;             /* this universe                    */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((vc= (struct VIEOS_CONTEXT *) clientData) == (struct VIEOS_CONTEXT *) 0
      || vc->VC_signature != SIG_VIEOS_CONTEXT
     )
  {
    Tcl_SetResult (interp, "unknown vieos context", TCL_STATIC);
    return TCL_ERROR;
  }

  if (argc < 1
      || (method= argv [1]) == (char *) 0
      || *method == 0
     )
    goto ERROR;

  if (abbrev ("version", method, 3))
  {
    Tcl_SetResult (interp, VIEOS_VERSION, TCL_STATIC);
    return TCL_OK;
  }

  /* BEGIN standard methods - - - - - - - - - - - - - - - */
  if (abbrev ("creator", method, 4))
  {
    struct VIEOS_CONTEXT *vc_up;        /* the creator of this context      */

    interp->result= ((vc_up= (struct VIEOS_CONTEXT *) vc->VC_context)
                    == (struct VIEOS_CONTEXT *) 0)
                    ? ""                /* the absolute creator             */
                    : vc_up->VC_name;
        
    return TCL_OK;
  }

  if (abbrev ("class", method, 3))
  {
    Tcl_SetResult (interp, "context", TCL_STATIC);
    return TCL_OK;
  }

  if (abbrev ("name", method, 3))
  {
    interp->result= vc->VC_name;
    return TCL_OK;
  }

  if (strcmp ("destroy", method) == 0)
  {
    Tcl_DeleteCommand (interp, vc->VC_name);
    vieos_destroy_context (vc);

    Tcl_SetResult (interp, "context destroyed", TCL_STATIC);
    return TCL_OK;
  }
  /* END standard methods - - - - - - - - - - - - - - - */

  if (argc >= 3)
  {
    object_name= argv [2];

    /* vieos00?.c */
    if (abbrev ("context", method, 6))
    {
      struct VIEOS_CONTEXT *vc_sub;

      if ((vc_sub= vieos_create_context (interp, vc, object_name))
          == (struct VIEOS_CONTEXT *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create context object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= vc_sub->VC_name;
      return TCL_OK;
    }

    /* vieos10?.c */
    if (abbrev ("markup", method, 3))
    {
      struct VIEOS_MARKUP *hto;

      if ((hto= vieos_create_markup (interp, vc, object_name))
          == (struct VIEOS_MARKUP *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create markup object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= hto->VIEM_name;
      return TCL_OK;
    }

    /* vieos20?.c */
    if (abbrev ("indexer", method, 3)
        || strcmp ("lmd", method) == 0
       )
    {
      struct VIEOS_INDEX *lmd;

      if ((lmd= vieos_create_index (interp, vc, object_name))
          == (struct VIEOS_INDEX *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create index object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= lmd->VIEI_name;
      return TCL_OK;
    }

    /* vieos30?.c */
    if (abbrev ("block", method, 5))
    {
      struct VIEOS_BLOCK *vb;

      if ((vb= vieos_create_block (interp, vc, object_name))
          == (struct VIEOS_BLOCK *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create block object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= vb->VIEB_name;
      return TCL_OK;
    }

    /* vieos40?.c */
    if (abbrev ("cluster", method, 5))
    {
      struct VIEOS_CLUSTER *vcl;

      if ((vcl= vieos_create_cluster (interp, vc, object_name))
          == (struct VIEOS_CLUSTER *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create generic object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= vcl->VCL_name;
      return TCL_OK;
    }

    /* vieosg0?.c */
    if (abbrev ("generic", method, 5))
    {
      struct VIEOS_GENERIC *vg;

      if ((vg= vieos_create_generic (interp, vc, object_name))
          == (struct VIEOS_GENERIC *) 0)
      {
        Tcl_SetResult (interp,
                       "can't create generic object", TCL_STATIC);
        return TCL_ERROR;
      }

      interp->result= vg->VIEG_name;
      return TCL_OK;
    }
  }

ERROR:
  Tcl_SetResult (interp, "unknown vieos command", TCL_STATIC);
  return TCL_ERROR;
}

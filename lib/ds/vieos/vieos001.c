/*
 *  FILE %ds/vieos/vieos001.c
 *
 *  create a new vieos context
 *
 *  written:       1995-03-19
 *  latest update: 1997-01-15 11:26:00
 *
 */

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_CONTEXT *vieos_create_context (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc_creator,
char *nm)
{
  struct VIEOS_CONTEXT *vc;

  if ((vc= (struct VIEOS_CONTEXT *)
            calloc (sizeof (struct VIEOS_CONTEXT), 1))
      != (struct VIEOS_CONTEXT *) 0)
  {
    vc->VC_name= strdup (nm);
    vc->VC_signature= SIG_VIEOS_CONTEXT;
    vc->VC_interp= interp;
    vc->VC_context= vc_creator;

    Tcl_CreateCommand (interp, nm,
                       vieos_context_object,
                       (ClientData) vc,
                       vieos_destroy_context);

    if (vc_creator != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc_creator->VC_SUB_CONTEXT, (unsigned char *) nm,
                       (long) vc);
  }

  return vc;
}

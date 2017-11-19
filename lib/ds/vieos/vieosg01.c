/*
 *  FILE %ds/vieos/vieosg01.c
 *
 *  create a vieos generic object
 *
 *  written:       1995-12-16
 *  latest update: 1996-03-17 19:33:45
 *
 */

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_GENERIC *vieos_create_generic (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc,
char *nm)
{
  struct VIEOS_GENERIC *vg;

  if ((vg= (struct VIEOS_GENERIC *)
            calloc (sizeof (struct VIEOS_GENERIC), 1))
      != (struct VIEOS_GENERIC *) 0)
  {
    vg->VIEG_name= strdup (nm);
    vg->VIEG_signature= SIG_VIEOS_GENERIC;
    vg->VIEG_interp= interp;
    vg->VIEG_context= vc;

    Tcl_CreateCommand (interp, nm,
                       vieos_generic_object,
                       (ClientData) vg,
                       vieos_destroy_generic);

    if (vc != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc->VC_GENERIC, nm, (long) vg);
  }

  return vg;
}

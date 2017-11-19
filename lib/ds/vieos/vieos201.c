/*
 *  FILE %ds/vieos/vieos201.c
 *
 *  call evaluation of a TCL script
 *
 *  written:       1995-12-14
 *  latest update: 1996-03-17 19:32:27
 *
 */

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include <gg/lookup.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_INDEX *vieos_create_index (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc,
char *nm)
{
  struct VIEOS_INDEX *idx;
  struct LMDC_CONTROL *lmdc;

  if ((idx= (struct VIEOS_INDEX *)
            calloc (sizeof (struct VIEOS_INDEX), 1))
         != (struct VIEOS_INDEX *) 0
      && (lmdc= lmd_create_control ()) != (struct LMDC_CONTROL *) 0
     )
  {
    idx->VIEI_name= strdup (nm);
    idx->VIEI_signature= SIG_VIEOS_INDEX;
    idx->VIEI_interp= interp;
    idx->VIEI_lmdc= lmdc;
    idx->VIEI_context= vc;

    Tcl_CreateCommand (interp, nm,
                       vieos_index_object,
                       (ClientData) idx,
                       vieos_destroy_index);

    if (vc != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc->VC_INDEX, (unsigned char *) nm, (long) idx);
  }

  return idx;
}

/*
 *  FILE %ds/vieos/vieos301.c
 *
 *  create a new vieos block object
 *
 *  written:       1995-12-16
 *  latest update: 1996-03-17 19:57:12
 *
 */

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include <gg/dyb.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_BLOCK *vieos_create_block (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc,
char *nm)
{
  struct VIEOS_BLOCK *vb;

  if ((vb= (struct VIEOS_BLOCK *)
            calloc (sizeof (struct VIEOS_BLOCK), 1))
      != (struct VIEOS_BLOCK *) 0)
  {
    vb->VIEB_name= strdup (nm);
    vb->VIEB_signature= SIG_VIEOS_BLOCK;
    vb->VIEB_interp= interp;
    vb->VIEB_context= vc;

    vb->VIEB_dyb= dyb_new_block (256);

    Tcl_CreateCommand (interp, nm,
                       vieos_block_object,
                       (ClientData) vb,
                       vieos_destroy_block);

    if (vc != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc->VC_BLOCK, (unsigned char *) nm, (long) vb);
  }

  return vb;
}

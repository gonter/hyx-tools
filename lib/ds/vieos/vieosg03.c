/*
 *  FILE %ds/vieos/vieosg03.c
 *
 *  destroy a generic object and all it's associated memory
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:36:12
 *
 */

#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_generic (ClientData clientData)
{
  struct VIEOS_GENERIC *vg;

  if ((vg= (struct VIEOS_GENERIC *) clientData) != (struct VIEOS_GENERIC *) 0
      && vg->VIEG_signature == SIG_VIEOS_GENERIC
     )
  {
    vg->VIEG_signature= 0L;             /* create an invalid signature      */
                                        /* in case someone comes across     */
                                        /* a dangling pointer...            */
    free_or_what (vg->VIEG_name);
    free (vg);
  }
}

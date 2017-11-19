/*
 *  FILE %ds/vieos/vieos403.c
 *
 *  destroy a cluster object and all it's associated memory
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:30:13
 *
 */

#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_cluster (ClientData clientData)
{
  struct VIEOS_CLUSTER *vcl;

  if ((vcl= (struct VIEOS_CLUSTER *) clientData) != (struct VIEOS_CLUSTER *) 0
      && vcl->VCL_signature == SIG_VIEOS_CLUSTER
     )
  {
    vcl->VCL_signature= 0L;             /* create an invalid signature      */
                                        /* in case someone comes across     */
                                        /* a dangling pointer...            */
    free_or_what (vcl->VCL_name);
    hcc_destroy (vcl->VCL_hcc);

    free (vcl);
  }
}

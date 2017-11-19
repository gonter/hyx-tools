/*
 *  FILE %ds/vieos/vieos401.c
 *
 *  create a vieos cluster object
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:29:44
 *  $Id: vieos401.c,v 1.3 2002/01/27 23:01:46 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <tcl.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_CLUSTER *vieos_create_cluster (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc,
char *nm)
{
  struct VIEOS_CLUSTER *vcl;
  struct HYX_CLUSTER_CONTROL *hcc;

  if ((vcl= (struct VIEOS_CLUSTER *)
            calloc (sizeof (struct VIEOS_CLUSTER), 1))
      != (struct VIEOS_CLUSTER *) 0)
  {
    vcl->VCL_name= strdup (nm);
    vcl->VCL_signature= SIG_VIEOS_CLUSTER;
    vcl->VCL_interp= interp;
    vcl->VCL_context= vc;

    vcl->VCL_hcc= hcc= hyx_new_cluster_control ();
    hcc_set_cluster_name (hcc, nm);

    Tcl_CreateCommand (interp, nm,
                       vieos_cluster_object,
                       (ClientData) vcl,
                       vieos_destroy_cluster);

    if (vc != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc->VC_GENERIC, (unsigned char *) nm, (long) vcl);
  }

  return vcl;
}

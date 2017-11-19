/*
 *  FILE %ds/hyxl/hyxl0007.c
 *
 *  written:       1995-12-16
 *  latest update: 1996-10-10  0:13:06
 *  $Id: hyxl0007.c,v 1.3 2002/01/27 23:01:44 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hcc_destroy (struct HYX_CLUSTER_CONTROL *hcc)
{
  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0) return -1;

  free_or_what (hcc->HCC_fnm_hyx);
  free_or_what (hcc->HCC_fnm_lut);
  free_or_what (hcc->HCC_fnm_idx);
  free_or_what (hcc->HCC_fnm_xfn);
  free_or_what (hcc->HCC_fnm_kill_by_id);
  free_or_what (hcc->HCC_fnm_kill_by_lx);

  free (hcc);

  return 0;
}

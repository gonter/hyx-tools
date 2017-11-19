/*
 *  FILE %ds/hyxl/hyxl0005.c
 *
 *  written:       1994-12-10
 *  latest update: 1996-10-10  0:12:56
 *  $Id: hyxl0005.c,v 1.3 2002/01/27 23:01:44 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hcc_set_cluster_name (struct HYX_CLUSTER_CONTROL *hcc, char *fnm_hyx)
{
  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0
      || fnm_hyx == (char *) 0
     ) return -1;

  free_or_what (hcc->HCC_fnm_hyx);
  
  hcc->HCC_fnm_hyx= strdup (fnm_hyx);

  fnmcpy3 (&hcc->HCC_fnm_lut, fnm_hyx, ".lut");
  fnmcpy3 (&hcc->HCC_fnm_idx, fnm_hyx, ".idx");
  fnmcpy3 (&hcc->HCC_fnm_xfn, fnm_hyx, ".xfn");
  fnmcpy3 (&hcc->HCC_fnm_kill_by_id, fnm_hyx, ".kid");
  fnmcpy3 (&hcc->HCC_fnm_kill_by_lx, fnm_hyx, ".klx");

  return 0;
}

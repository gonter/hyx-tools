/*
 *  FILE %ds/hyxl/hyxl0013.c
 *
 *  written:       2002-01-28
 *  latest update: 2002-01-28 19:09:11
 *  $Id: hyxl0013.c,v 1.3 2010/05/04 00:03:22 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
HYX_CLUSTER_CONTROL *new_HYX_CLUSTER_CONTROL (char *fnm_hyx)
{
  struct HYX_CLUSTER_CONTROL *p;

  if ((p= hyx_new_cluster_control ()) == (struct HYX_CLUSTER_CONTROL *) 0)
  {
ERROR:
    return (struct HYX_CLUSTER_CONTROL *) 0;
  }

  if (hcc_set_cluster_name (p, fnm_hyx) == -1)
  {
    hcc_destroy (p);
    p->HCC_next_index= 1L;
    goto ERROR;
  }

  return p;
}

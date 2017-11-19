/*
 *  FILE %ned/08/ned0844b.c
 *
 *  destroy a cluster control block
 *
 *  written:       1996-09-29
 *  latest update: 1999-04-25 16:33:09
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_free_clusterctrl (struct CLUSTERCTRL *cl)
{
  if (cl == (struct CLUSTERCTRL *) 0) return -1;

  free_or_what (cl->cluster_name_logic);
  free_or_what (cl->cluster_name_hyx);
  free_or_what (cl->cluster_name_lut);
  free_or_what (cl->cluster_name_xfn);
  free_or_what (cl->cluster_name_idx);

  free (cl);

  return 0;
}

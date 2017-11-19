/*
 *  FILE %ds/hyxdb/hyxdb001.c
 *
 *  hyxdb: HYX Database Management
 *  create a new dabase handle
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 11:22:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
struct HYXDB_CONTROL *hyxdb_new_handle (
char *cluster_name,
int open_mode)
{
  struct HYXDB_CONTROL *hdl= (struct HYXDB_CONTROL *) 0;
  struct HYX_CLUSTER_CONTROL *hcc;

  if ((hdl= (struct HYXDB_CONTROL *) calloc (sizeof (struct HYXDB_CONTROL), 1))
            == (struct HYXDB_CONTROL *) 0)
    return (struct HYXDB_CONTROL *) 0;

  /** T2D: remote clusteres **/
  hdl->HYXDB_clc= hcc= hyx_new_cluster_control ();
  hcc_set_cluster_name (hcc, cluster_name);
  hcc_open (hcc, open_mode);

  return hdl;
}

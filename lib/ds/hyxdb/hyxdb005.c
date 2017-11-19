/*
 *  FILE %ds/hyxdb/hyxdb005.c
 *
 *  hyxdb: HYX Database Management
 *  load a object from a frame
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 11:22:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
struct HYXDB_OBJECT *hyxdb_load_object_frame (
struct HYXDB_CONTROL *ctrl,
char *frame_name)
{
  struct HYX_CLUSTER_CONTROL *hcc;
  long size;

  if (ctrl == (struct HYXDB_CONTROL *) 0
      || (hcc= ctrl->HYXDB_clc) == (struct HYX_CLUSTER_CONTROL *) 0
      || frame_name == (char *) 0 || *frame_name == 0
     )
    return (struct HYXDB_OBJECT *) 0;

  size= hcc_seek_by_name (hcc, frame_name);

  return hyxdb_parse_stream (ctrl, hcc->HCC_f_hyx, size, frame_name);
}

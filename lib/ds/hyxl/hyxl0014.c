/*
 *  FILE %ds/hyxl/hyxl0014.c
 *
 *  written:       2002-07-16
 *  $Id: hyxl0014.c,v 1.1 2002/07/17 07:19:40 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hcc_add_frame (
struct HYX_CLUSTER_CONTROL *hcc,
char *frame_name)
{
  return ytree_set_value (&hcc->HCC_ytree, frame_name, hcc->HCC_next_index++);
}

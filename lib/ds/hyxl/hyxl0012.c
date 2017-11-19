/*
 *  FILE %ds/hyxl/hyxl0012.c
 *
 *  seek to a frame referenced
 *  return size of the frame
 *
 *  see: also: hyx_seek_by_name ()
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 12:41:55
 *  $Id: hyxl0012.c,v 1.2 2002/01/27 23:01:44 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/fileio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hcc_seek_by_name (struct HYX_CLUSTER_CONTROL *hcc, char *frame_name)
{
  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0
      || hcc->HCC_open_mode == HCC_om_error
      || (hcc->HCC_open_mode == HCC_om_closed
          && hcc_open (hcc, HCC_om_read) == -1
         )
     ) return -1L;

  return hyx_seek_by_name (hcc->HCC_f_hyx, hcc->HCC_f_idx,
                           hcc->HCC_f_lut, hcc->HCC_f_xfn,
                           frame_name);
}

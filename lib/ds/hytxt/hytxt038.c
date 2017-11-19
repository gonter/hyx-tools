/*
 *  FILE %ds/hytxt/hytxt038.c
 *
 *  find a frame in the lut or xfn file
 *  *** DONT USE *** hyx_get_index does more ...
 *
 *  written:       1997-11-01
 *  latest update: 1997-11-02 14:00:11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long find_frame_lut_or_xfn (FILE *lut, FILE *xfn, char *fr_name)
{
  int rc;
  int lng;
  long w_info;
  long rv= -1;

  if (lut != (FILE *) 0)
  {
    fseek (lut, 0L, 0);
    rc= lookup_file (lut, fr_name, &w_info, &lng);
    if (rc & LOOKUP_found) rv= w_info;
  }

  if (rv != -1 && xfn != (FILE *) 0)
  {
    /* Note: fseek (xfn, 0L, 0) is done inside lookup_file_xfn */
    rc= lookup_file_xfn (xfn, fr_name, &w_info);
    if (rc & LOOKUP_found) rv= w_info;
  }

  return rv;
}

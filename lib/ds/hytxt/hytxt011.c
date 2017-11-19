/*
 *  FILE %ds/hytxt/hytxt011.c
 *
 *  written:       1991 07 20
 *  latest update: 1997-11-01 10:38:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long find_frame_lut (FILE *lut, char *fr_name)
{
  int rc;
  long w_info;
  int lng;

  if (lut == (FILE *) 0) return -1L;

  fseek (lut, 0L, 0);
  rc= lookup_file (lut, fr_name, &w_info, &lng);

  return (rc & LOOKUP_found) ? w_info : -1L;
}

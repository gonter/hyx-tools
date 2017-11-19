/*
 *  FILE %ds/hytxt/hytxt012.c
 *
 *  written:       1991 07 20
 *  latest update: 1996-03-24 17:42:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long find_frame_xfn (FILE *xfn, char *fr_name)
{
  int rc;
  long w_info;

  if (xfn == (FILE *) 0) return -1L;

  rc= lookup_file_xfn (xfn, fr_name, &w_info);

  return (rc & LOOKUP_found) ? w_info : -1L;
}

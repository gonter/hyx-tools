/*
 *  FILE %ds/hytxt/hytxt037.c
 *
 *  processing of LUT-files
 *
 *  written:       1996-10-12
 *  latest update: 1996-10-13 12:18:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_dump_frame_list (FILE *fi_lut, FILE *fi_xfn)
{
  int rc;

  if (fi_lut != (FILE *) 0)
  {
    fseek (fi_lut, 0L, 0);
    rc= lut_process_block (fi_lut, lut_dump_entry, (void *) 0);
  }

  if (fi_xfn != (FILE *) 0)
  {
    fseek (fi_xfn, 0L, 0);
    rc= xfn_process_block (fi_xfn, lut_dump_entry, (void *) 0);
  }

  return 0;
}

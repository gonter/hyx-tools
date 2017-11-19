/*
 *  FILE %ds/lut/lut_0014.c
 *
 *  processing of XFN-files
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

/* ------------------------------------------------------------------------ */
int xfn_dump_file (char *fn, int out_mode, long dump_start)
{
  return xfn_process (fn, lut_dump_entry, (void *) out_mode, dump_start);
}

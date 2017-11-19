/*
 *  FILE %ds/lut/lut_0012.c
 *
 *  processing of LUT-files
 *
 *  written:       1996-10-12
 *  latest update: 1996-10-13 12:18:48
 *  $Id: lut_0012.c,v 1.2 2001/09/10 06:58:43 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lut_dump_file (char *fn, int out_mode, long dump_start)
{
  return lut_process (fn, lut_dump_entry, (void *) out_mode, dump_start);
}

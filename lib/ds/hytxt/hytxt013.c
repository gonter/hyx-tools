/*
 *  FILE %ds/hytxt/hytxt013.c
 *
 *  written:       1991 07 20
 *  latest update: 1996-03-24 18:44:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int deref_index (FILE *fidx, long idx, long *p1, long *p2, long *p3)
{
  if (fidx == (FILE *) 0) return -1;

  fseek (fidx, idx * ((long) HYXIDX_REC_SIZE), 0);
  *p1= dpp_fread_long (fidx, 4);
  *p2= dpp_fread_long (fidx, 4);
  *p3= dpp_fread_long (fidx, 4);
  if (feof (fidx)) return -1;

  return 0;
}

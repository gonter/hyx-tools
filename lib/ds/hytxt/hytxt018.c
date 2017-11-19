/*
 *  FILE %ds/hytxt/hytxt018.c
 *
 *  written:       1994-02-04
 *  latest update: 1996-03-24 17:44:43
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gg/dpp.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_get_random_index (FILE *fi_idx)
{
  long siz;
  long x;

  if (fi_idx == (FILE *) 0) return -1L;

  fseek (fi_idx, (long) 0, 2);
  siz= ftell (fi_idx);
  siz /= HYXIDX_REC_SIZE;

  x= random_long ();

  return (x % siz) + 1L;
}

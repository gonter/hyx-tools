/*
 *  FILE %sgml/hyxadd01.c
 *
 *  add files as frames to a HYX cluster
 *  -  used in hyxadd.c
 *
 *  written:       1994-06-04
 *  latest update: 1999-04-24 11:59:55
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/filename.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_add (char *fn_hyx, struct FILE_SEGMENT *segments, int verbose_mode)
{
  char *afn;
  char *fnm_idx;
  char *fnm_lut;
  char *fnm_xfn;
  int rc;

  if (fn_hyx == (char *) 0 || !*fn_hyx) return -2;

printf ("hyx_add: %s\n", fn_hyx);

  if ((afn= translate_logic_filename (fn_hyx)) == (char *) 0) afn= fn_hyx;

  fnm_idx= fnmcpy2 (afn, ".idx");
  fnm_lut= fnmcpy2 (afn, ".lut");
  fnm_xfn= fnmcpy2 (afn, ".xfn");

  rc= hyx_update (afn, fnm_idx, fnm_lut, fnm_xfn, segments, verbose_mode);

  free (fnm_idx);
  free (fnm_lut);
  free (fnm_xfn);

  return rc;
}

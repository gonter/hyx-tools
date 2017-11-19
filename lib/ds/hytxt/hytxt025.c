/*
 *  FILE %sgml/hytxt025.c
 *
 *  purge hypertext clusters
 *
 *  written:       1991 02 16
 *                 1992 12 07: revision
 *                 1994-10-23: isolated from hyxpurge.c
 *  latest update: 1999-04-25 16:57:48
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/hytxt.h>
#include <gg/filename.h>

#ifndef MSDOS
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
int hyx_purge (char *hyx_in, int verbose_level)
{
  int rc;
  char *afn;
  char *hyx_out;
  char *idx_in;
  char *idx_out;
  char *xx;

  if (hyx_in == (char *) 0 || !*hyx_in) return -2;

  if ((afn= translate_logic_filename (hyx_in)) == (char *) 0) afn= hyx_in;
  hyx_out= fnmcpy2 (afn, ".h@x");
  idx_in=  fnmcpy2 (afn, ".idx");
  idx_out= fnmcpy2 (afn, ".i@x");

  rc= hyx_purge2 (idx_in, idx_out, afn, hyx_out, verbose_level);

  if (rc == 0)
  {
    xx= fnmcpy2 (afn, ".@hx");
    unlink (xx);
    rename (afn, xx);
    rename (hyx_out, afn);
    free (xx);

    xx= fnmcpy2 (hyx_out, ".@ix");
    unlink (xx);
    rename (idx_in, xx);
    rename (idx_out, idx_in);
    free (xx);
  }

  free (afn);
  free (hyx_out);
  free (idx_in);
  free (idx_out);

  return rc;
}

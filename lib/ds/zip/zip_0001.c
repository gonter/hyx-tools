/*
 *  FILE %ds/zip/zip_0001.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-26
 *  $Id: zip_0001.c,v 1.3 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_quick_scan (char *fnm)
{
  FILE *fi;
  long cde_pos;

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0) return -1;
  cde_pos= zip_find_cde_start (fi, 0x1000L);
  printf ("CDE @0x%08lX\n", cde_pos);
}

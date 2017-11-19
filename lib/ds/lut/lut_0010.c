/*
 *  FILE %ds/lut/lut_0010.c
 *
 *  processing of XFN-files
 *
 *  written:       1995-01-07
 *  latest update: 1996-10-13 12:21:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int xfn_process (
char *xfn_name,                         /* XFN file name                    */
int (*processor) (char *w, long i, void *client_data),
void *client_data,
long start)
{
  FILE *xfn;
  int rc;

  if ((xfn= fopen (xfn_name, "rb")) == (FILE *) 0) return -1;
  fseek (xfn, start, 0);
  rc= xfn_process_block (xfn, processor, client_data);
  fclose (xfn);

  return rc;
}

/*
 *  FILE %ds/url/url_0005.c
 *
 *  URL handling
 *
 *  written:       1995-12-25
 *  latest update: 1996-03-18  8:05:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/url.h>

/* ------------------------------------------------------------------------ */
int url_write_object_name (char *url_interface, char *outfile)
{
  FILE *fo;

  if (url_interface == (char *) 0 || *url_interface == 0) return 0;

  if (outfile == (char *) 0
      || *outfile == 0
      || (fo= fopen (url_interface, "w")) == (FILE *) 0
     ) return -1;

  fprintf (fo, "object %s\n", outfile);
  fclose (fo);

  return 0;
}

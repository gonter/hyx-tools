/*
 *  FILE ~/usr/sbr/copyfil0.c
 *
 *  File Copy
 *  - see also: copyfile.c
 *
 *  written:       1994-07-17 (extracted from ..
 *  latest update: 1994-12-09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int copyfile (char *src, char *dst)
{
  FILE *fi;
  FILE *fo;
  int ch;

  if ((fi= fopen (src, "rb")) == (FILE *) 0) return -1;
  if ((fo= fopen (dst, "wb")) == (FILE *) 0)
  {
    fclose (fi);
    return -1;
  }

  for (;;)
  {
    ch= fgetc (fi);
    if (feof (fi)) break;
    fputc (ch, fo);
  }

  fclose (fi);
  fclose (fo);

  return 0;
}

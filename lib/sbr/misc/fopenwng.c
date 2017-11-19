/*
 *  FILE ~/usr/sbr/fopenwng.c
 *
 *  open file and print warning, if that failed
 *
 *  written:       1995-04-26
 *  latest update: 1995-05-12
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
FILE *fopen_wng (char *fnm, char *mode)
{
  FILE *f;

  if (fnm == (char *) 0 || *fnm == 0)
  {
    fprintf (stderr, "wng: can't open unnamed file\n");
    return (FILE *) 0;
  }

  if (mode == (char *) 0 || *mode == 0)
  {
    fprintf (stderr, "wng: can't open file %s without mode!\n");
    return (FILE *) 0;
  }

  if ((f= fopen (fnm, mode)) == (FILE *) 0)
  {
    fprintf (stderr, "wng: can't open file \"%s\" in mode \"%s\"\n",
             fnm, mode);
    return (FILE *) 0;
  }

  return f;
}

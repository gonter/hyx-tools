/*
 *  FILE ~/usr/sbr/file2low.c
 *
 *  written:       1994-12-31: extracted from %usr/utl/tolower.c
 *  latest update: 1995-08-15
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/fileio.h>

/* ------------------------------------------------------------------------ */
#ifdef TO_UPPER
#define FILE_TO_WHATEVER        file_to_upper
#define WHATEVER_CASE           upper_case
#endif /* TO_UPPER */

#ifdef TO_LOWER
#define FILE_TO_WHATEVER        file_to_lower
#define WHATEVER_CASE           lower_case
#endif /* TO_LOWER */

/* ------------------------------------------------------------------------ */
int FILE_TO_WHATEVER (char *fn, FILE *fo)
{
  FILE *fi;
  int ch;

  if ((fi= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "can't open File %s!\n", fn);
    return -1;
  }

  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    if (ch == 0x0D) continue;
    ch= WHATEVER_CASE (ch);
    fputc (ch, fo);
  }

  fclose (fi);

  return 0;
}

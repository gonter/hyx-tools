/*
 *  FILE ~/usr/ds/tfb/plz2tfb.c
 *
 *  written:       1993-11-20
 *  latest update: 1993-11-20
 *
 */

#include <stdio.h>

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

/* ------------------------------------------------------------------------ */
#define HEADER_OFFSET   0x00C2
#define RECORD_SIZE     53
static char RECORD [1024];

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv[]);
int cdecl plz2tfb (char *fni, FILE *fo);
int cdecl xtrans (FILE *fo, char *ch, int siz);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i;

  for (i= 1; i<argc; i++) plz2tfb (argv[i], stdout);

  return 0;
}

/* ------------------------------------------------------------------------ */
int plz2tfb (char *fni, FILE *fo)
{
  FILE *fi;
  int rc;

  if ((fi= fopen (fni, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "plz2tfb: can't open file %s\n", fni);
    return -1;
  }

  rc= fseek (fi, (long) HEADER_OFFSET, 0);
  for (;;)
  {
    fread (RECORD, RECORD_SIZE, 1, fi);
    if (feof (fi) && rc <= 0) break;
    xtrans (fo, RECORD+30, 4);
    fputc (':', fo);
    xtrans (fo, RECORD+34, 5);
    fputc (':', fo);
    xtrans (fo, RECORD+39, 5);
    fputc (':', fo);
    xtrans (fo, RECORD+43, 8);
    fputc (':', fo);
    xtrans (fo, RECORD, 30);
    fputc ('\n', fo);
  }
  fclose (fi);

  return 0;
}

/* ------------------------------------------------------------------------ */
int xtrans (FILE *fo, char *str, int siz)
{
  int blanks= 0;
  int ch;

  while (siz-- > 0)
  {
    ch= (int) *str++;
    if (ch == ' ')
    {
      blanks++;
    }
    else
    {
      for (; blanks>0; blanks--) fputc (' ', fo);
      fputc (ch, fo);
    }
  }
  return 0;
}

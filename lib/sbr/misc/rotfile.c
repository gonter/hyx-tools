/*
 *  FILE %sbr/rotfile.c
 *
 *  rotate a file
 *  - used in: %usr/utl/rotate.c
 *
 *  written:       1992-02-19
 *  latest update: 1997-05-30 13:03:05
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>

#define EXTRA_BUFFERS
#ifdef EXTRA_BUFFERS
#include <stdlib.h>
static char *buf1, *buf2;
#define BUFFER_SIZE 40960
#endif

static char tmpnm[300];
static char rotnm[300];

/* ------------------------------------------------------------------------ */
int rotate_file (
char *fn,
FILE *fo,
int verbose_mode,
int decode_it,
int rotate_names)
{
  FILE *fi;
  FILE *xfo;
  int ch;
  int ch2;

  xfo= fo;

  if ((fi= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1;
  }

#ifdef EXTRA_BUFFERS
  setvbuf (fi, buf1, _IOFBF, BUFFER_SIZE);
#endif
  if (decode_it)
  {
    fnmcpy (tmpnm, fn, "$pv");
    xfo= fopen (tmpnm, "wb");
    if (xfo == (FILE *) 0) return -1;
#ifdef EXTRA_BUFFERS
    setvbuf (xfo, buf2, _IOFBF, BUFFER_SIZE);
#endif
  }

  if (xfo != (FILE *) 0)
  {
    for (;;)
    {
      ch= fgetc (fi) & 0x00FF;
      if (feof (fi)) break;
      ch2= ((ch & 0x000F) << 4) | ((ch & 0x00F0) >> 4);
      fputc (ch2, xfo);
    }
    fclose (fi);
  }

  if (decode_it)
  {
    if (xfo != (FILE *) 0) fclose (xfo);
    unlink (fn);
    if (rotate_names)
    {
      strcpy (rotnm, fn);
      rotate13 (rotnm);
      if (verbose_mode > 0) printf ("%s renamed to %s\n", fn, rotnm);
      rename (tmpnm, rotnm);
    }
    else rename (tmpnm, fn);
  }
  else
  {
    if (rotate_names)
    {
      strcpy (rotnm, fn);
      rotate13 (rotnm);
      if (verbose_mode > 0) printf ("%s renamed to %s\n", fn, rotnm);
      rename (fn, rotnm);
    }
  }

  return 0;
}

/*
 *  FILE ~/usr/sgml/hyxeng03.c
 *
 *  written:       1990 04 13: aus File HYX.C isoliert
 *  latest update: 1994-12-11
 *
 */

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/keys.h>
#include <gg/hytxt.h>
#include <gg/strings.h>
#include "hyxeng.h"

static char filenm2 [66];
static char filenmt [66];

/* ------------------------------------------------------------------------ */
int hy_purge (
char *fn,
int verbose_mode)
{
  struct stat buf;
  int  i, j, rv;

  if (access (fn, 0) != 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2;
  }

  for (i= strlen (fn) -1; i >= 0; i--)
    if (fn [i] == '\\' || fn [i] == ':') break;

  if (i >= 0)
  {
    i++;
    strncpy (filenm2, fn, i);
    filenm2 [i] = 0;
  }
  else i= j= 0;

  strcpy (&filenm2 [i], "_BAK_FTR.NED");
  if (stat (filenm2, &buf) == -1 ||
      !(buf.st_mode & S_IFDIR))  /* Directory ??? */
  {
    j= i;
  }
  else
  {
    j= strlen (filenm2);
    filenm2 [j++] = '\\';
    filenm2 [j  ] = 0;
  }

  for (;;)
  {
    if (fn [i] == '.' || fn [i] == 0) break;
    filenm2 [j++] = fn [i++];
  }

  strcpy (&filenm2 [j], ".@HY");
  strcpy ( filenmt, fn);
  strcpy (&filenmt [i], ".$Y$");

  if (verbose_mode > 1)
  {
    printf ("i=%d  j=%d\n", i, j);
    printf ("%s\n", fn);

    blanks (stdout, i);
    fputc ('^', stdout);
    fputc ('\n', stdout);
    printf ("%s\n", filenm2);

    blanks (stdout, j);
    fputc ('^', stdout);
    fputc ('\n', stdout);
  }

  if (verbose_mode > 0)
  {
    printf ("Purge %s -> %s (%s) -: ", fn, filenm2, filenmt);
    i = kbin ();
    if (i == 0x1B) { printf ("ESC\n"); return -1; }
    if (i == 'n' || i == 'N') { printf ("NO\n"); return -2; }
  }

  rv= hytxt_purge (fn, filenm2, filenmt);
  if (verbose_mode > 0) printf ("%d\n", rv);
  if (rv == 0)
  {
    unlink (fn);
    rename (filenmt, fn);
  }
  return 0;
}

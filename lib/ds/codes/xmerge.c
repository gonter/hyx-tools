/*
 *  FILE ~/usr/dpp/codes/xmerge.c
 *
 *  merge two files
 *
 *  written:       1993-01-01: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1999-04-25 16:57:30
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINESIZE 78

/* ------------------------------------------------------------------------ */
struct ATT
{
  struct ATT *ATT_next;

  char *ATT_match;
  char *ATT_add;
  int ATT_printed;
} ;

/* ------------------------------------------------------------------------ */
static struct ATT *attlist= (struct ATT *) 0;
static struct ATT **aatt= &attlist;

#define L_SIZE 256
static char l1 [L_SIZE];
static char l2 [L_SIZE];

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv[]);
int cdecl read_attlist (char *fn);
int cdecl add_up (char *fn);
int cdecl new_ones (void);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf (stderr, "error: to few parameters!\n");
    return 1;
  }

  read_attlist (argv[1]);
  add_up (argv[2]);
  new_ones ();

  return 0;
}

/* ------------------------------------------------------------------------ */
int read_attlist (char *fn)
{
  FILE *fi;
  struct ATT *natt;

  fi = fopen (fn, "r");
  if (fi == (FILE *) 0)
  {
    fprintf (stderr, "error: can't open '%s' for reading!\n", fn);
    return -1;
  }

  for (;;)
  {
    fscanf (fi, "%s%[^\n]", l1, l2);
    if (feof (fi)) break;
    fgetc (fi);

    if ((natt= (struct ATT *) calloc (sizeof (struct ATT), 1))
        == (struct ATT *) 0)
    {
      fprintf (stderr, "error: can't allocate memory!\n");
      return -1;
    }
    natt->ATT_match= strdup (l1);
    natt->ATT_add= strdup (l2);
    *aatt= natt;
     aatt= &natt->ATT_next;
  }
  fclose (fi);

  return 0;
}

/* ------------------------------------------------------------------------ */
int add_up (char *fn)
{
  FILE *fi;
  char *matchstr;
  int matching;
  struct ATT *xa;

  fi = fopen (fn, "r");
  if (fi == (FILE *) 0)
  {
    fprintf (stderr, "error: can't open '%s' for reading!\n", fn);
    return -1;
  }

  for (;;)
  {
    fscanf (fi, "%[^\n]", l1);
    if (feof (fi)) break;
    fgetc (fi);

    matching=0;
    for (xa= attlist; xa != (struct ATT *) 0; xa= xa->ATT_next)
    {
      if ((matchstr= strstr (l1, xa->ATT_match)) != (char *) 0)
      {
        matching=1;
        xa->ATT_printed=1;
        break;
      }
    }
    fputs (l1, stdout);
    if (matching)
    {
      if (strlen (l1) + strlen (xa->ATT_add) > MAX_LINESIZE)
        fputs ("\n  ", stdout);
      fputs (xa->ATT_add, stdout);
    }
    putchar ('\n');
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int new_ones ()
{
  struct ATT *xa;

  for (xa= attlist; xa != (struct ATT *) 0; xa= xa->ATT_next)
    if (xa->ATT_printed == 0)
    {
      printf ("#>>> %s%s\n", xa->ATT_match, xa->ATT_add);
    }

  return 0;
}

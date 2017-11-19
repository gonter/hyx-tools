/*
 *  FILE %ned/12/ned1299.c
 *
 *  NED's diagnostic stuff
 *
 *  written:       1996-07-22
 *  latest update: 1996-07-22 10:23:57
 *
 */

#include <stdio.h>

/* ------------------------------------------------------------------------ */
int ned_diag_argv (int argc, char *argv [])
{
  int i;

  fprintf (stderr, "argc=%d\n", argc);
  for (i= 0; i < argc; i++)
    fprintf (stderr, "argv [%d]= '%s'\n", i, argv [i]);

  return 0;
}

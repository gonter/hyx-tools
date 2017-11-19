/*
 *  FILE ~/usr/sbr/dt001t.c
 *
 *  module for testing printing of the current date and time
 *
 *  written:       1994-07-23
 *  latest update: 1994-07-23
 *
 */

#include <time.h>
#include <gg/sbr.h>

static char line [256];
main ()
{
  long tt;

  tt= time ((long *) 0);
  printf ("tt=0x%08lX\n", tt);
  _actual_datim (line, 1, tt);
  printf ("line=%s\n", line);
  return 0;
}


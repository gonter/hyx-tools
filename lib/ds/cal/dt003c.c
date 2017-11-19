/*
 *  FILE %ds/cal/dt003b.c
 *
 *  print current date in a readable format in
 *  one large word
 *
 *  written:       2000-01-16
 *  latest update: 2000-01-16 20:19:00
 *
 */

#include <stdio.h>
#include <time.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

int main (int argc, char *argv [])
{
  printf ("%ld\n", time ((long *) 0));
}


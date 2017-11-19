/*
 *  FILE %sbr/dirt_014.c
 *
 *  print an array of integers in C format
 *
 *  written:       1995-08-30
 *  latest update: 1997-08-15 21:27:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>

#define NUM_ENTRIES 16

#ifdef DTYPE_int
#define DTYPE int
#define FMT1 "%3d,"
#define FMT2 "%3d"
#define fnc print_int_table
#endif

#ifdef DTYPE_long
#define DTYPE long
#define FMT1 "%3ld,"
#define FMT2 "%3ld"
#define fnc print_long_table
#endif

/* ------------------------------------------------------------------------ */
int fnc (FILE *fo, DTYPE *cpi, int num)
{
  int i;

  num--;
  fputs ("{\n  ", fo);
  for (i= 0; i < num; i++)
  {
    fprintf (fo, FMT1, *cpi++);
    if ((i % NUM_ENTRIES) == NUM_ENTRIES-1) fputs ("\n  ", fo);
  }

  fprintf (fo, FMT2, *cpi);
  fputs ("\n} ;\n\n", fo);

  return 0;
}

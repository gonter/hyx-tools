/*
 *  FILE %sbr/dirt_011.c
 *
 *  written:       1990 04 12
 *  latest update: 1995-10-26
 *
 */

#pragma check_stack(off)

#include <gg/dirty.h>

/* ------------------------------------------------------------------------ */
int VAL (char *f, int s)
{
  return (f [s] & 0x00FF)* 256 + (f [s+1] & 0x00FF);
}

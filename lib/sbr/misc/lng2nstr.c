/*
 *  FILE %sbr/lng2nstr.c
 *
 *  convert a long (32bit) integer into a printable string in sortable
 *  notation
 *  see also: lng2hex.c
 *
 *  written:       1995-12-28
 *  latest update: 1995-12-28
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int long_to_num_string (long bin, char *hex)
{
  int lng;

  sprintf (hex+2, "%d", (int) bin);

  lng= strlen (hex+2);
  if (lng >= 0 && lng <= 9) *hex= (char) lng + '0'; else
  if (lng >= 10 && lng <= 36) *hex= (char) lng + 'A' - 10; else
  hex [1]= ':';

  return 0;
}

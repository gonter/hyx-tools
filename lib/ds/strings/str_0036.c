/*
 *  FILE %ds/strings/str_0036.c
 *
 *  set values into a character table
 *
 *  written:       1994-09-17
 *  latest update: 1995-12-08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int str_prompt (char *txt, char *dest, int lng, char *tmp, char *preset)
{
  if (preset != (char *) 0) strncpy (dest, preset, lng);

  printf ("%s [%s]: ", txt, dest);

  if (fread_line (stdin, tmp, lng) > 0)
    strncpy (dest, tmp, lng);

  return 0;
}

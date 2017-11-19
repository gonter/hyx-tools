/*
 *  FILE ~/usr/sbr/str_0021.c
 *
 *  written:       1993-04-24
 *  latest update: 1994-10-02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int match_array (               /* match a list of strings                  */
char *patterns [],              /* possible patterns                        */
int pattern_count,              /* number of patterns in array              */
char  *string)                  /* string to find in patterns               */
{
  int i;

  for (i= 0; i < pattern_count; i++)
    if (match (patterns[i], string) > 0) return i;

  return -1;
}

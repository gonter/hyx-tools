/*
 *  FILE %ds/strings/str_0017.c
 *
 *  written:       1992 12 08
 *  latest update: 1996-01-29  8:43:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *str_assign (char **d, char *s)
{
  free_or_what (*d);
  *d= (s == (char *) 0) ? (char *) 0 : strdup (s);

  return *d;
}

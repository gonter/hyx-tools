/*
 *  FILE %ds/strings/str_0051.c
 *
 *  duplicate a string if not a null pointer
 *
 *  written:       1997-06-13
 *  latest update: 1997-06-13 14:04:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strdup_or_what (char *s)
{
  if (s == (char *) 0) return (char *) 0;
  return strdup (s);
}

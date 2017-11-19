/*
 *  FILE %ds/strings/str_0038.c
 *
 *  return actual string or undef-string
 *
 *  written:       1995-01-29
 *  latest update: 1995-11-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *str_or_undef (char *s)
{
  return (s == (char *) 0 || *s == 0) ? "???" : s;
}

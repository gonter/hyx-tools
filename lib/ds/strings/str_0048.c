/*
 *  FILE %ds/strings/str_0048.c
 *
 *  return string for debugging
 *
 *  written:       1996-03-17
 *  latest update: 1996-03-17 16:28:02
 *
 */

#include <gg/strings.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
char *XSTR (char *str)
{
  return (str == (char *) 0) ? "(null)" : str;
}

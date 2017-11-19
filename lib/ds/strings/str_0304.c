/*
 *  FILE 1996-11-26 19:26:14
 *
 *  written:       1996-11-26
 *  latest update: 1999-04-25 16:59:09
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#ifdef __HPUX__
#define _XOPEN_SOURCE
#endif

#include <stdlib.h>
#include <memory.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strdup_max (char *str, int max_size)
{
  char *cp;
  int size;

  if (str == (char *) 0 || max_size < 0) return (char *) 0;

  cp= str;
  for (size= 0; size < max_size; size++)
    if (*cp++ == 0) break;

  if ((cp= malloc (size + 1)) != (char *) 0)
  {
    memcpy (cp, str, size);
    cp [size]= 0;
  }

  return cp;
}

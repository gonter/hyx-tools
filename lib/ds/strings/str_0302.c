/*
 *  FILE %ds/strings/str_0302.c
 *
 *  written:       1992 12 14
 *  latest update: 1999-04-25 16:58:42
 *  $Id: str_0302.c,v 1.4 2005/09/04 09:24:40 gonter Exp $
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
char *strndup (const char *str, size_t size)
{
  char *cp;

  if (str == (char *) 0 || size < 0) return (char *) 0;

  if ((cp= malloc (size + 1)) != (char *) 0)
  {
    memcpy (cp, str, size);
    cp [size]= 0;
  }

  return cp;
}

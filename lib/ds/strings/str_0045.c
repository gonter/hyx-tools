/*
 *  FILE %ds/strings/str_0045.c
 *
 *  written:       1995-11-11
 *  latest update: 1995-11-11
 *  $Id: str_0045.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strdup_extra (const char *str, int extra)
{
  char *cp;

  if (str == (char *) 0) return (char *) 0;

  if ((cp= malloc (strlen (str) + 1 + extra)) != (char *) 0)
    strcpy (cp, str);

  return cp;
}

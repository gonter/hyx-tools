/*
 *  FILE %ds/strings/str_0301.c
 *
 *  written:       1991 01 27
 *                 1992 09 13: revision
 *  latest update: 1999-04-25 16:58:51
 *  $Id: str_0301.c,v 1.3 2002/02/04 08:13:10 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#ifdef __HPUX__
#define _XOPEN_SOURCE
#endif

#include <stdlib.h>

#ifdef MSDOS
int strlen (char *);
char *strcpy (char *, char *);
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strdup (const char *str)
{
  char *cp;

  if (str == (char *) 0) return (char *) 0;

  if ((cp= malloc (strlen (str) + 1)) != (char *) 0)
  {
    strcpy (cp, str);
  }

  return cp;
}

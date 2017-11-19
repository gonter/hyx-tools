/*
 *  FILE ~/usr/sbr/str_0303.c
 *
 *  written:       1994-04-02
 *  latest update: 1999-04-25 16:59:00
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#ifdef __HPUX__
#define _XOPEN_SOURCE
#endif

#include <string.h>
#include <stdlib.h>

#ifdef MSDOS
int strlen(char *);
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strrev (char *str)
{
  char *cp1;
  char *cp2;
  char ch;

  if (str == (char *) 0) return (char *) 0;

  cp1= str;
  cp2= str+strlen (str)-1;
  for (; cp1 < cp2; cp1++, cp2--)
  {
    ch= *cp1;
    *cp1= *cp2;
    *cp2= ch;
  }

  return str;
}

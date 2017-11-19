/*
 *  FILE %ds/strings/str_0049.c
 *
 *  copy string with a given maximum length
 *  similar to strncpy, except that the buffer is not cleared out
 *  and that a 0 character is always put at the end of the string
 *
 *  written:       1996-09-28
 *  latest update: 1997-06-16 19:50:39
 *  $Id: str_0049.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strcpy_max (      /* string copy with maximum length                  */
char *d,                /* destination                                      */
const char *s,           /* source                                           */
int size)               /* maximal cnt Zeichen in Dest; d [cnt]=0;          */
{
  char *rv;

  if ((rv= d) == (char *) 0
      || s == (char *) 0
      || size <= 0
     ) return (char *) 0;

  while (--size > 0) if ((*d++= *s++) == 0) return rv;
  *d= (char) 0;

  return rv;
}

/*
 *  FILE %ds/strings/str_0052.c
 *
 *  copy string with a given maximum length
 *
 *  similar to strncpy, except that the buffer is not cleared out
 *  and that a 0 character is always put at the end of the string
 *  furthermore: the number of chars copied is returned
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 18:54:15
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strcpy2_max (       /* string copy with maximum length                  */
char *d,                /* destination                                      */
char *s,                /* source                                           */
int size)               /* maximal cnt Zeichen in Dest; d [cnt]=0;          */
{
  int rv= 0;

  if (d == (char *) 0
      || s == (char *) 0
      || size <= 0
     ) return 0;

  while (--size > 0) { if ((*d++= *s++) == 0) return rv; rv++; }
  *d= (char) 0;

  return rv;
}

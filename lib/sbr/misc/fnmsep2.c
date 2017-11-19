/*
 *  FILE %sbr/fnmsep2.c
 *
 *  remove extension from a file name
 *
 *  written:       1994-12-28
 *  latest update: 1995-12-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *remove_extension (char *s)
{
  int i;

  for (i= strlen (s)-1; i >= 0; i--)
    switch (s [i] )
    {
      case '.':
        s [i]= 0;

#ifdef MSDOS
      case '\\':
#endif
      case '/':
        i= 0;
        break;
    }

  return s;
}


/*
 *  FILE %sbr/tellext.c
 *
 *  return extension of a file name
 *
 *  written:       1994-12-28
 *  latest update: 1997-09-14 16:19:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *tell_extension (char *s)
{
  int i;

  for (i= strlen (s)-1; i >= 0; i--)
    switch (s [i] )
    {
      case '.':
        return &s [i+1];

#ifdef MSDOS
      case '\\':
#endif
      case '/':
        i= 0;
        break;
    }

  return &s [strlen (s)];    /* Filename ohne Extension */
}

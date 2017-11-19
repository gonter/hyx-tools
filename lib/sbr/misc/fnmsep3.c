/*
 *  FILE %sbr/fnmsep3.c
 *
 *  return pointer to filename only from a full path
 *
 *  written:       1995-11-05
 *  latest update: 1997-09-14 16:43:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#ifndef __GG_CMS__
#include <gg/filename.h>
#endif

/* ------------------------------------------------------------------------ */
char *get_filename_from_path (char *s) /* s.a: isolate_path */
{
  int i;

  if (s == (char *) 0) return (char *) 0;

  for (i= strlen (s)-1; i >= 0; i--)
    if (s [i] == '/'
#ifdef MSDOS
        || s [i] == '\\'
#endif
       ) return &s [i+1];

  return s;
}

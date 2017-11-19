/*
 *  FILE ~/usr/sbr/envbinsr.c
 *
 *  env_bin_search: find a file following an environment variable
 *
 *  written:       1994-08-13: variation of env_file_search (envfilsr.c)
 *  latest update: 1999-04-25 17:00:01
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>

#ifdef MSDOS
#pragma check_stack(off)
#include <io.h>
#else
#include <unistd.h>
#endif

#ifndef NIL
#define NIL (void *) 0
#endif

/* ------------------------------------------------------------------------ */
char *env_bin_search (char *fn, char *env, char *ext [], int n_ext)
{
  char tmp [66];
  char *envv;
  int i;
  int j;
  int l;

  if (fn == (char *) 0
      || *fn == 0
      || env == (char *) 0
      || *env == 0
      || (envv= getenv (env)) == (char *) 0)
    return (char *) 0;

  while (*envv)
  {
    for (i= 0; envv[i]; i++)
      if (envv [i] == ';') break;

    if (i+strlen(fn)+1 < 66)
    {
      strncpy (tmp, envv, i);
      tmp [i]= '\\';
      strcpy (&tmp [i + ((tmp [i-1] == '\\' || tmp [i-1] == '/')
                        ? 0 : 1)], fn);
      l= strlen (tmp);
      for (j= 0; j<n_ext; j++)
      {
        strcpy (tmp+l, ext [j]);
        if (access (tmp, 0) == 0) return strdup (tmp);
      }
    }
    envv= &envv[i];
    if (*envv == 0) break;
    envv++;
  }

  return (char *) 0;
}

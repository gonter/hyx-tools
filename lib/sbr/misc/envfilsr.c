/*
 *  FILE ~/usr/sbr/envfilsr.c
 *
 *  env_file_search: find a file following an environment variable
 *
 *  written:       1992 02 08
 *  latest update: 1999-04-25 17:00:11
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
#define PATH_SEP     '\\'
#define PATH_ENV_SEP ';'
#else
#include <unistd.h>
#define PATH_SEP     '/'
#define PATH_ENV_SEP ':'
#endif

#ifndef NIL
#define NIL (void *) 0
#endif

/* ------------------------------------------------------------------------ */
char *env_file_search (char *fn, char *env)
{
  char tmp [66];
  char *envv;
  int i;

  if (fn == (char *) 0
      || *fn == 0
      || env == (char *) 0
      || *env == 0
      || (envv= getenv (env)) == (char *) 0)
    return (char *) 0;

  while (*envv)
  {
    for (i= 0; envv[i]; i++)
      if (envv [i] == PATH_ENV_SEP) break;

    if (i+strlen (fn)+1 < 66)
    {
      strncpy (tmp, envv, i);
      tmp [i]= PATH_SEP;
#ifdef MSDOS
      strcpy (&tmp[i + ((tmp [i-1] == '/' || tmp [i-1] == '\\') ? 0 :1)], fn);
#else
      strcpy (&tmp[i + ((tmp [i-1] == '/') ? 0 : 1)], fn);
#endif
      if (access (tmp, 0) == 0) return strdup (tmp);
    }

    envv= &envv [i];
    if (*envv == 0) break;
    envv++;
  }

  return (char *) 0;
}

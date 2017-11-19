/*
 *  FILE %sbr/fnmcpy2.c
 *
 *  copy filename and replace its extension or filetype (under CMS)
 *  - result is malloced
 *
 *  written:       1994-12-09
 *  latest update: 1996-09-29  9:00:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *fnmcpy2 (char *fnm_old, char *ext)
{
  char *fnm_new= (char *) 0;

  if ((fnm_new= malloc (strlen (fnm_old) + strlen (ext) + 2)) != (char *) 0)
    fnmcpy (fnm_new, fnm_old, ext);

  return fnm_new;
}

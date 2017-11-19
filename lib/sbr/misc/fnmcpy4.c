/*
 *  FILE %sbr/fnmcpy4.c
 *
 *  copy filename if given or create a new one by combining
 *  a given other file name and an extension
 *
 *  written:       1995-12-10
 *  latest update: 1995-12-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *fnmcpy4 (char *fnm1, char *fnm2, char *ext)
{
  return (fnm1 == (char *) 0 || *fnm1 == 0)
         ? fnmcpy2 (fnm2, ext)
         : strdup (fnm1);
}

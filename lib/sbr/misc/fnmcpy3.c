/*
 *  FILE %sbr/fnmcpy3.c
 *
 *  copy filename and replace its extension or filetype (under CMS)
 *
 *  written:       1995-07-30
 *  latest update: 1995-12-16
 *  $Id: fnmcpy3.c,v 1.2 2005/09/04 09:24:40 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *fnmcpy3 (char **dst, char *fnm_old, char *ext)
{
  free_or_what (*dst);
  *dst= fnmcpy2 (fnm_old, ext);
  return *dst;
}

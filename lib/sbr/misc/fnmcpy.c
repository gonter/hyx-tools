/*
 *  FILE %sbr/fnmcpy.c
 *
 *  copy filename and replace its extension or filetype (under CMS)
 *
 *  written:       1987 04 08
 *                 1991 02 09: revision
 *                 1991 05 17: rename c:/usr/ned/04/ned0407.c
 *                                 to c:/usr/sbr/fnmcpy.c
 *                             gen_extension() -> fnmcpy()
 *  latest update: 1995-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
#ifndef __CMS__
int fnmcpy (char *fnm_new, char *fnm_old, char *extension)
{
  int i, j;

  if (fnm_new == (char *) 0) return -1;
  strcpy (fnm_new, fnm_old);
  i= strlen (fnm_new);

  for (j= i-1; j >= 0; j--)
  {
    if (fnm_new [j] == '.')
    {
      strcpy (&fnm_new [j], extension);
      return 0;
    }
    if (fnm_new [j] == '\\'
        || fnm_new [j] == '/'
        || fnm_new [j] == ':') break;
  }

  if (extension == (char *) 0 || extension [0] == 0)
  {
    fnm_new [i] = 0;
    return 0;
  }

  strcpy (&fnm_new [i], extension);
  return 0;
}
#endif

/* ------------------------------------------------------------------------ */
#ifdef __CMS__
int fnmcpy (char *fnm_new, char *fnm_old, char *extension)
{
  int ch;
  int dots= 0;

  if (fnm_new == (char *) 0) return -1;

  for (; ch= *fnm_old;)
  {
    *fnm_new= (char) ch;
    if (ch == '.') break;
    fnm_new++;
    fnm_old++;
  }

  for (fnm_old++; ch= *fnm_old;)
  {
    if (ch == '.') break;
    fnm_old++;
  }

  if (*extension != '.')
  {
    *fnm_new++ = '.';
    dots++; 
  }

  for (; ch= *extension;)
  {
    *fnm_new= (char) ch;
    if (ch == '.')
    {
      if (dots == 2) break;
      dots++;
    }
    fnm_new++;
    extension++;
  }

  if (dots == 1)
    for (; ch= *fnm_old;)
    {
      *fnm_new= (char) ch;
      if (ch == '.')
      {
        if (dots == 2) break;
        dots++;
      }
      fnm_new++;
      fnm_old++;
    }

  *fnm_new= 0;

  return 0;
}
#endif

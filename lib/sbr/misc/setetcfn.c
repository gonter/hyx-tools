/*
 *  FILE %sbr/setetcfn.c
 *
 *  set a filename pointing into the /etc directory
 *
 *  written:       1991 09 18
 *                 1991 12 13: moved to /usr/sbr
 *                             (before: /usr/ned/12/ned1202.c)
 *  latest update: 1999-04-25 17:00:50
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>

#ifdef MSDOS
#define DEFAULT_ETC "c:/etc"
#else
#ifdef __CMS__
#define DEFAULT_ETC ""
#else
#endif
#define DEFAULT_ETC "/usr/local/etc"
#endif

/* ------------------------------------------------------------------------ */
char *set_etc_filename (char *dst, char *fnm)
{
  char *etc;
  int l1;

  etc= getenv ("ETC");
  if (etc == (char *) 0) etc= DEFAULT_ETC;
  l1= strlen (etc);
  if (dst == (char *) 0) dst= malloc (l1 + strlen (fnm) + 2);
  strcpy (dst, etc);
  if (l1 > 0
#ifdef MSDOS
      && dst [l1-1] != '\\'
#endif
      && dst [l1-1] != '/')
  {
    dst [l1++]= '/';
    dst [l1]= 0;
  }

  strcpy (dst+l1, fnm);

  return dst;
}

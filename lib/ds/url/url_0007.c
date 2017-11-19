/*
 *  FILE %ds/url/url_0007.c
 *
 *  URL handling
 *
 *  written:       1995-11-26
 *  latest update: 1996-03-18 21:41:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/url.h>

/* ------------------------------------------------------------------------ */
char *url_fetch_file (char *url, void *cd)
{
  char *dst= (char *) 0;

#ifdef MSDOS
  cd;
#endif /* MSDOS */

  if (url == (char *) 0) return (char *) 0;

  if (strncmp ("//", url, 2) == 0)
  { /* host is contained */
    url += 2;
    if (strncmp ("localhost/", url, 10) == 0)
      dst= strdup (url+9); /* check for the slash but also return it */
  }
  else
  {
    if (*url == '/') dst= strdup (url);
  }

  return dst;
}

/*
 *  FILE %ds/url/url_0005.c
 *
 *  isolate url schema
 *
 *  written:       1996-03-17
 *  latest update: 1996-04-05 15:02:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/url.h>

/* ------------------------------------------------------------------------ */
char *url_isolate_schema (char *url)
{
  int i;
  int ch;
  char *schema;

  if (url == (char *) 0 || *url == 0) return (char *) 0;

  for (i= 0;; i++)
  {
    if ((ch= url [i] & 0x00FF) == 0) return (char *) 0;
    if (ch == ':') break;
  }

  if ((schema= malloc (i+1)) == (char *) 0) return (char *) 0;
  strncpy (schema, url, i);
  schema [i]= 0;

  return schema;
}

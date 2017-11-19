/*
 *  FILE %ds/url/url_0009.c
 *
 *  ... trash...
 *  URL handling
 *
 *  written:       1996-03-23
 *  latest update: 1999-04-25 16:59:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/url.h>

static char *URL_INTERFACE= "@@urlint.@@@";

#define TMP_SIZE 1024

/* ------------------------------------------------------------------------ */
char *url_fetch_mailto (char *url, void *cd)
{
  char *dst= (char *) 0;
  char *tmp;
  char *url_interface;
  int method;

  if ((tmp= malloc (TMP_SIZE)) == (char *) 0
      || (url_interface= set_tmp_filename ((char *) 0, URL_INTERFACE))
         == (char *) 0
     )
    return (char *) 0;

  method= (int) cd;

  sprintf (tmp, "gmail -z -u%s %s%s",
           url_interface,
           (method == URL_TYPE_reply) ? "-r" : "",
           url);

  system (tmp);
  dst= url_read_object_name (url_interface, (char *) 0, -1);

  free_or_what (tmp);
  free_or_what (url_interface);

  return dst;
}

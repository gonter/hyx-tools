/*
 *  FILE %ds/url/url_0002.c
 *
 *  URL handling
 *
 *  written:       1995-11-26
 *  latest update: 1999-04-25 16:59:21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include <gg/url.h>

/* ------------------------------------------------------------------------ */
char *url_fetch (char *url)
{
  struct URL_HANDLER *uh;
  URL_Processor *fetch;

  if (url == (char *) 0
      || *url == 0
      || (uh= url_get_handler (url)) == (struct URL_HANDLER *) 0
      || (fetch= uh->URL_fetcher) == (URL_Processor *) 0
     ) return (char *) 0;

  if (uh->URL_drop_schema) url += uh->URL_schema_length + 1;

  return (*fetch) (url, uh->URL_client_data);
}

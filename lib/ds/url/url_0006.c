/*
 *  FILE %ds/url/url_0006.c
 *
 *  URL handling
 *
 *  written:       1995-11-26
 *  latest update: 1996-03-17 23:37:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/url.h>

/* ------------------------------------------------------------------------ */
int url_identify_type (char *url)
{
  struct URL_HANDLER *url_handler;

  if ((url_handler= url_get_handler (url)) != (struct URL_HANDLER *) 0)
    return url_handler->URL_type;

  return URL_TYPE_none;
}

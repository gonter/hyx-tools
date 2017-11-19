/*
 *  FILE %ds/url/url_0001.c
 *
 *  URL handling
 *
 *  written:       1995-11-26
 *  latest update: 1996-08-08 17:09:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/url.h>

/* ------------------------------------------------------------------------ */
static struct URL_HANDLER *url_handlers= (struct URL_HANDLER *) 0;
static struct URL_HANDLER **url_next_handler= &url_handlers;
static struct YTREE *url_schemes= (struct YTREE *) 0;
static int initialized= 0;

/* ------------------------------------------------------------------------ */
struct URL_HANDLER *url_get_handler (char *url)
{
  struct URL_HANDLER *rc= (struct URL_HANDLER *) 0;
  struct YTREE *yt;
  char *schema;

  if (!initialized) url_initialize ();

  if ((schema= url_isolate_schema (url)) != (char *) 0
      && (yt= ytree_lookup_word (url_schemes, (unsigned char *) schema))
         != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW)
     )
    rc= (struct URL_HANDLER *) yt->YT_info;

  free_or_what (schema);

  return rc;
}

/* ------------------------------------------------------------------------ */
struct URL_HANDLER *url_register_handler (
char *schema,
int type,
int drop_schema,
URL_Processor *fetcher,
void *cd)
{
  struct URL_HANDLER *url_handler;
  struct YTREE *yt;

  if (!initialized) url_initialize ();

  if (schema == (char *) 0
      || *schema == 0
      || (yt= ytree_insert_word (&url_schemes, (unsigned char *) schema))
              == (struct YTREE *) 0
     ) return (struct URL_HANDLER *) 0;

  if (yt->YT_flags & YTflag_EOW)
  { /* url handler was already registerd; overwrite ... */
    url_handler= (struct URL_HANDLER *) yt->YT_info;
  }
  else
  { /* url handler is new, create control structure; */
    if ((url_handler= (struct URL_HANDLER *)
                       calloc (sizeof (struct URL_HANDLER), 1))
         == (struct URL_HANDLER *) 0
       ) return (struct URL_HANDLER *) 0;

    yt->YT_flags |= YTflag_EOW;
    yt->YT_info= (long) url_handler;

    url_handler->URL_schema= strdup (schema);
    url_handler->URL_schema_length= strlen (schema);

    *url_next_handler=  url_handler;
     url_next_handler= &url_handler->URL_next;
  }

  url_handler->URL_type= type;  
  url_handler->URL_drop_schema= drop_schema;  
  url_handler->URL_fetcher= fetcher;
  url_handler->URL_client_data= cd;

  return url_handler;
}

/* ------------------------------------------------------------------------ */
int url_initialize ()
{
  initialized= 1;

  url_register_handler ("file",   URL_TYPE_file, 1,
                        url_fetch_file, (void *) 0);

#ifdef MSDOS
  url_register_handler ("mailto", URL_TYPE_mailto, 1,
                        url_fetch_mailto, (void *) URL_TYPE_mailto);
  url_register_handler ("reply",  URL_TYPE_reply, 1,
                        url_fetch_mailto, (void *) URL_TYPE_reply);
#endif /* MSDOS */

  return 0;
}

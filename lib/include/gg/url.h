/*
 *  include FILE <gg/url.h>
 *
 *  methods
 *  data structures
 *  constants
 *  prototypes
 *
 *  written:       1995-11-26
 *  latest udpate: 1996-03-18  8:00:56
 *
 */

#ifndef __GG_url__
#define __GG_url__

#include <gg/floskel.h>

/* methods: --------------------------------------------------------------- */
typedef char *URL_Processor (char *url, void *cd);

/* data structures: ------------------------------------------------------- */
struct URL_HANDLER
{
  struct URL_HANDLER *URL_next;

  char *URL_schema;
  int URL_schema_length;
  int URL_type;
  int URL_drop_schema;                  /* 1 -> remove schema for process.  */
  URL_Processor *URL_fetcher;
  void *URL_client_data;
} ;

/* constants: ------------------------------------------------------------- */
#define URL_TYPE_error         -1
#define URL_TYPE_none           0
#define URL_TYPE_ftp            1
#define URL_TYPE_file           2
#define URL_TYPE_http           3
#define URL_TYPE_wais           4
#define URL_TYPE_news           5
#define URL_TYPE_newsrc         6
#define URL_TYPE_gopher         7
#define URL_TYPE_mailto         8
#define URL_TYPE_reply          9
#define URL_TYPE_something     99

/* prototypes: ------------------------------------------------------------ */
struct URL_HANDLER *cdecl url_get_handler (char *url);
struct URL_HANDLER *cdecl url_register_handler (char *schema, int type,
                      int drop_schema, URL_Processor *fetcher, void *cd);
int cdecl url_initialize (void);

char *cdecl url_fetch (char *url);
int cdecl url_write_object_name (char *url_interface, char *url_file);
char *cdecl url_read_object_name (char *url_interface,
              char *tmp_space, int tmp_size);
char *cdecl url_isolate_schema (char *url);
int cdecl url_identify_type (char *url);
char *cdecl url_fetch_file (char *url, void *cd);
char *cdecl url_fetch_mailto (char *url, void *cd);

#endif /* __GG_url__ */

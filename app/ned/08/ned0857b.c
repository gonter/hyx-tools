/*
 *  FILE %ned/08/ned0857b.c
 *
 *  T2D:
 *  - caching of feature lookup results
 *
 *  see also ned_lookup_feature ()
 *
 *  written:       1996-05-24
 *  latest update: 1997-08-28 13:30:52
 *  $Id: ned0857b.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
int ned_lookup_tag (
const char *token,              /* string to be searched                    */
char *line_buffer,              /* string to hold feature buffer            */
char **field_fnm,               /* pointer to feature string                */
char **field_location,          /* type of the the feature string           */
int MAX_BUFFER)                 /* size of line buffer                      */
{
  struct ARRAY_ELEMENT *e_crf;
  char *act_tag_file;
  int rc;
  int token_length;

  if (field_fnm == (char **) 0
      || field_location == (char **) 0
      || ned_main_context == (struct NED_CONTEXT *) 0
     ) return -1;

  token_length= ned_main_context->NED_CTX_tag_length;

  for (e_crf= array_top (ned_main_context->NED_CTX_tag_files);
       e_crf != (struct ARRAY_ELEMENT *) 0;
       e_crf= e_crf->next)
  {
    act_tag_file= translate_logic_filename ((char *) e_crf->payload);

    rc= tfb_get_tag_entry (token, act_tag_file, (char *) 0,
                           line_buffer, field_fnm, field_location,
                           MAX_BUFFER, token_length);

    free_or_what (act_tag_file);

    if (rc == 1) return 0;
  }

  return -1;
}

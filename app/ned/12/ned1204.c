/*
 *  FILE %ned/12/ned1204.c
 *
 *  written:       1995-12-12
 *  latest update: 1999-04-25 16:36:42
 *  $Id: ned1204.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_add_context (
struct NED_CONTEXT *ctx,
int what,
const char *file_name,
int at_top)
{
  struct ARRAY_CONTROL **ac;

  if (ctx == (struct NED_CONTEXT *) 0) return -1;

  switch (what)
  {
    case NED_CTXitem_crf:
      ac= &ctx->NED_CTX_crf;
      break;

    case NED_CTXitem_lib:
      ac= &ctx->NED_CTX_lib;
      break;

    case NED_CTXitem_lexicon:
      ac= &ctx->NED_CTX_lex;
      break;

    case NED_CTXitem_thesaurus:
      ac= &ctx->NED_CTX_thes;
      break;

    case NED_CTXitem_tag_file:
      ac= &ctx->NED_CTX_tag_files;
      break;

    case NED_CTXitem_feature_table:
      ac= &ctx->NED_CTX_feature_tables;
      break;

    default:            /* unknown item! */
      return -1;
  }

  if (*ac == (struct ARRAY_CONTROL *) 0
      && (*ac= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return -1;

  if (at_top)
       array_unshift (*ac, (void *) strdup (file_name));
  else array_push    (*ac, (void *) strdup (file_name));

  return 0;
}

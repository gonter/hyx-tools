/*
 *  FILE %ned/12/ned1206.c
 *
 *  written:       1995-12-12
 *  latest update: 1996-12-03 17:11:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
char *ned_get_context (struct NED_CONTEXT *ctx, int what)
{
  struct ARRAY_CONTROL *ac;
  struct ARRAY_ELEMENT *e_crf;
  char *crf;

  if (ctx == (struct NED_CONTEXT *) 0) return (char *) 0;

  switch (what)
  {
    case NED_CTXitem_crf:
      ac= ctx->NED_CTX_crf;
      break;

    case NED_CTXitem_lib:
      ac= ctx->NED_CTX_lib;
      break;

    case NED_CTXitem_lexicon:
      ac= ctx->NED_CTX_lex;
      break;

    case NED_CTXitem_thesaurus:
      ac= ctx->NED_CTX_thes;
      break;

    case NED_CTXitem_tag_file:
      ac= ctx->NED_CTX_tag_files;
      break;

    case NED_CTXitem_feature_table:
      ac= ctx->NED_CTX_feature_tables;
      break;

    default:
      return (char *) 0;
  }

  if (ac == (struct ARRAY_CONTROL *) 0) return (char *) 0;

  for (e_crf= ac->top;
       e_crf != (struct ARRAY_ELEMENT *) 0;
       e_crf= e_crf->next)
  {
    if ((crf= (char *) e_crf->payload) != (char *) 0
        && *crf != 0
       ) return crf;
  }

  return (char *) 0;
}

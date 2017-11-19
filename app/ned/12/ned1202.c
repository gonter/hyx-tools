/*
 *  FILE %ned/12/ned1202.c
 *
 *  written:       1995-12-12
 *  latest update: 1997-04-08  8:42:21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/hyx.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

#define ACTX(n,v) ned_add_context (ctx, (n), (v), 0)

/* ------------------------------------------------------------------------ */
int ned_default_context (struct NED_CONTEXT *ctx)
{
  if (ctx == (struct NED_CONTEXT *) 0) return -1;

  ctx->NED_IH_TOS= 0;           /* next stack position */

  if (   ACTX (NED_CTXitem_crf,           "%crf")       != 0
#ifdef MSDOS
      || ACTX (NED_CTXitem_crf,           "%cl1")       != 0
      || ACTX (NED_CTXitem_lib,           "%lib")       != 0
      || ACTX (NED_CTXitem_feature_table, "%feature")   != 0
      || ACTX (NED_CTXitem_tag_file,      "tags")       != 0
      || ACTX (NED_CTXitem_lexicon,       "%lex")       != 0
      || ACTX (NED_CTXitem_thesaurus,     "%thes")      != 0
#endif /* MSDOS */
     )
    return -1;

  ned_add_tag_rule (ctx, "calendar", hyx_rule_calendar, (void *) 0);

  return 0;
}

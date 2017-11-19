/*
 *  FILE %ned/12/ned1203.c
 *
 *  written:       1995-12-12
 *  latest update: 1999-04-25 16:36:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_destroy_context (struct NED_CONTEXT *ctx)
{
  if (ctx == (struct NED_CONTEXT *) 0) return -1;

  array_dispose_string (ctx->NED_CTX_crf);
  array_dispose_string (ctx->NED_CTX_lib);
  array_dispose_string (ctx->NED_CTX_tag_files);
  array_dispose_string (ctx->NED_CTX_feature_tables);
  free (ctx);

  return 0;
}

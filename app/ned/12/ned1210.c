/*
 *  FILE %ned/12/ned1210.c
 *
 *  add a feature table file to the current editor context
 *
 *  written:       1996-05-25
 *  latest update: 1996-11-10  1:15:07
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
int ned_add_feature_table (
struct NED_CONTEXT *ctx,
char *feature_table)
{
  if (ctx == (struct NED_CONTEXT *) 0) return -1;
  array_push2_dup (&ctx->NED_CTX_feature_tables, feature_table);

  return 0;
}

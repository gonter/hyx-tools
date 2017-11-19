/*
 *  FILE %ned/12/ned1209.c
 *
 *  written:       1996-05-25
 *  latest update: 1996-11-10  1:14:02
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
int ned_add_tag_file (
struct NED_CONTEXT *ctx,
char *tag_name)
{
  if (ctx == (struct NED_CONTEXT *) 0) return -1;
  array_push2_dup (&ctx->NED_CTX_tag_files, tag_name);

  return 0;
}

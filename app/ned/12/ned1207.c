/*
 *  FILE %ned/12/ned1207.c
 *
 *  push input handler to stack and return number of elements on stack
 *
 *  written:       1996-01-31 22:47:32
 *  latest update: 1996-11-10  1:06:37
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
int ned_push_input_handler (
struct NED_CONTEXT *ctx,
ned_input_handler *ih,
void *client_data)
{
  int tos;

  if (ctx == (struct NED_CONTEXT *) 0
      || (tos= ctx->NED_IH_TOS) >= NED_IH_SIZE
      || tos < 0
     ) return -1;

  ctx->NED_input_stack [tos]= ih;
  ctx->NED_input_stack_cd [tos]= client_data;
  tos++;
  ctx->NED_IH_TOS= tos;

  return tos;
}

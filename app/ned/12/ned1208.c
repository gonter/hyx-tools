/*
 *  FILE %ned/12/ned1208.c
 *
 *  pop input handler from stack and return number of elements on stack
 *
 *  written:       1996-01-31
 *  latest update: 1997-06-13 13:40:13
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
int ned_pop_input_handler (
struct NED_CONTEXT *ctx,
ned_input_handler **ih,
void **client_data)
{
  int tos;

  if (ctx == (struct NED_CONTEXT *) 0
      || ih == (ned_input_handler **) 0
      || client_data == (void **) 0
      || (tos= ctx->NED_IH_TOS) <= 0
     ) return -1;

  tos--;
  *ih= ctx->NED_input_stack [tos];
  *client_data= ctx->NED_input_stack_cd [tos];
  ctx->NED_IH_TOS= tos;

  return tos;
}

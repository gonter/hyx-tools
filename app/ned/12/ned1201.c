/*
 *  FILE %ned/12/ned1201.c
 *
 *  written:       1995-12-12
 *  latest update: 1999-04-25 16:36:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct NED_CONTEXT *ned_create_context ()
{
  struct NED_CONTEXT *ctx;

  if ((ctx= (struct NED_CONTEXT *) calloc (sizeof (struct NED_CONTEXT), 1))
            == (struct NED_CONTEXT *) 0
     )
    return (struct NED_CONTEXT *) 0;

  return ctx;
}

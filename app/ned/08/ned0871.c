/*
 *  FILE %ned/08/ned0871.c
 *
 *  written:       1991 09 25
 *  latest update: 1998-08-15 11:45:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "edctx.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;
extern char *default_start_frame;

/* ------------------------------------------------------------------------ */
void p_activate_crf ()
{
  char *crf;

  if ((crf= ned_get_context (ned_main_context, NED_CTXitem_crf))!=(char *) 0)
    ned_activate_special (crf, default_start_frame, -1);
}

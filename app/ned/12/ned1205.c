/*
 *  FILE %ned/12/ned1205.c
 *
 *  written:       1995-12-12
 *  latest update: 1999-04-25 16:36:49
 *  $Id: ned1205.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_add_tag_rule (
struct NED_CONTEXT *ctx,
const char *rule_name,
NED_tag_rule *tr,
void *client_data)
{
  struct NED_TAG_RULE_DESCRIPTOR *trd;

  if (ctx == (struct NED_CONTEXT *) 0
      || tr == (NED_tag_rule *) 0
      || (trd= (struct NED_TAG_RULE_DESCRIPTOR *)
               calloc (sizeof (struct NED_TAG_RULE_DESCRIPTOR), 1))
            == (struct NED_TAG_RULE_DESCRIPTOR *) 0
     ) return -1;

  if (rule_name != (char *) 0) trd->name= strdup (rule_name);
  trd->tr= tr;
  trd->client_data= client_data;

  array_push2 (&ctx->NED_CTX_tag_rules, (void *) trd);

  return 0;
}

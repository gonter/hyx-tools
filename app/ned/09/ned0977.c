/*
 *  FILE %ned/09/ned0977.c
 *
 *  parse a macro definition string
 *
 *  written:       1994-08-14: extracted from %ned/08/ned0908.c
 *  latest update: 1996-01-31 22:23:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int mac_parse (char *tokens, int mac_type)
{
  char *token [2];
  int n_tokens;

  if ((n_tokens= isolate_tokens (tokens, token, 2)) < 2) return -1;
  return mac_definition (token [0], token [1], mac_type);
}

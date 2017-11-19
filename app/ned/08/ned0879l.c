/*
 *  FILE %ned/08/ned0879l.c
 *
 *  written:       1996-12-03
 *  latest update: 1996-12-03 17:19:57
 *  $Id: ned0879l.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_lookup_lexicon ()
{
  set_repeat_command (ned_lookup_lexicon);
  ned_cross_ref ((char *) 0, 0, CRF_IN_LEX, CRF_GLOBAL, 1);
}

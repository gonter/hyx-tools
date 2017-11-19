/*
 *  FILE %ned/08/ned0879t.c
 *
 *  written:       1996-12-03
 *  latest update: 1996-12-03 17:19:57
 *  $Id: ned0879t.c,v 1.2 2005/04/01 16:46:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_lookup_thesaurus ()
{
  set_repeat_command (ned_lookup_thesaurus);
  ned_cross_ref ((char *) 0, 0, CRF_IN_THES, CRF_GLOBAL, 1);
}

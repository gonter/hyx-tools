/*
 *  FILE %ned/08/ned0879i.c
 *
 *  written:       1996-12-03
 *  latest update: 1996-12-03 17:19:57
 *  $Id: ned0879i.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_lookup_lib ()
{
  set_repeat_command (ned_lookup_lib);
  ned_cross_ref ((char *) 0, 0, CRF_IN_LIB, CRF_GLOBAL, 0);
}

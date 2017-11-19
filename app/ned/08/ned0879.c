/*
 *  FILE %ned/08/ned0879.c
 *
 *  written:       1991 10 23
 *  latest update: 1997-02-23 10:35:54
 *  $Id: ned0879.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_cross_ref ()
{
  ned_cross_ref ((char *) 0, 0, CRF_IN_CRF, CRF_GLOBAL_AND_LOCAL, 1);
}

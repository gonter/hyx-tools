/*
 *  FILE %ned/08/ned0876.c
 *
 *  written:       1991 10 12
 *  latest update: 1998-08-15 11:35:45
 *  $Id: ned0876.c,v 1.2 2002/06/15 04:35:21 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_activate_fr_notes ()
{
  ned_activate_special ((char *) 0, "$$notes", -1);
}

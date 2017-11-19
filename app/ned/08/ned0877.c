/*
 *  FILE %ned/08/ned0877.c
 *
 *  written:       1991 10 12
 *  latest update: 1998-08-15 11:35:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_activate_fr_help ()
{
  ned_activate_special ((char *) 0, "$$help", -1);
}

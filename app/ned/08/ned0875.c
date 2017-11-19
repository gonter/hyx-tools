/*
 *  FILE %ned/08/ned0875.c
 *
 *  written:       1991 10 12
 *  latest update: 1999-12-20 21:48:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern char *default_start_frame;

/* ------------------------------------------------------------------------ */
void p_activate_fr_root ()
{
  ned_activate_special ((char *) 0, default_start_frame, -1);
}

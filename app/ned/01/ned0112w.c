/*
 *  FILE %ned/01/ned0112w.c
 *
 *  WordStar standard table
 *
 *  written:       1994-12-26
 *  latest update: 1996-05-16 15:32:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
void p_ctrlw ()
{
  pfx= P_NONE;
}

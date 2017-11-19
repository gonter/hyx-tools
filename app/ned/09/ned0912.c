/*
 *  FILE %ned/09/ned0912.c
 *
 *  written:       1992 07 12: aus ned0903.c abgeleitet
 *  latest update: 1997-10-26 11:12:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern char stp_fnm [];
extern int oper_level;

/* ------------------------------------------------------------------------ */
int p_rdsetup ()
{
  if (oper_level >= LEV_STP) return -2;
  /* rst_button (); */ /* ##### dunno... shall we?? */

  return ned_read_setup (stp_fnm);
}

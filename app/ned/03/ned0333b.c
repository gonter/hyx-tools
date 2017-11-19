/*
 *  FILE %ned/03/ned0333b.c
 *
 *  written:       1991 11 08
 *  latest update: 1996-12-29 22:26:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_save_reload ()
{
  ned_save_reload (aw, WCTDM_no_change);
}

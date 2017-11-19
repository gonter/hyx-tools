/*
 *  FILE %ned/08/ned0867b.c
 *
 *  written:       1996-07-28
 *  latest update: 1998-08-15 12:30:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_memorize_location ()
{
  ned_wc_memorize_location (aw);
}

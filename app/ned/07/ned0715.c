/*
 *  FILE %ned/07/ned0715.c
 *
 *  set the block end marker
 *
 *  written:       1987 04 08
 *  latest update: 1997-06-29 12:41:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_blkend ()
{
  ned_set_marker (aw, ')');
}

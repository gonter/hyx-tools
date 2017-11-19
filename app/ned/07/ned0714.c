/*
 *  FILE %ned/07/ned0714.c
 *
 *  set the block begin marker
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-06-29 12:41:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_blkbeg ()
{
  ned_set_marker (aw, '(');
}

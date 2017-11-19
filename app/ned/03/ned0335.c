/*
 *  FILE %ned/03/ned0335.c
 *
 *  toggle character case at cursor postion
 *
 *  written:       1994-07-20
 *  latest update: 1997-01-19  0:51:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
void p_toggle_case ()
{
  q_insert (0x0100, 1);
}

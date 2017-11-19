/*
 *  FILE ~/usr/ned/08/ned0857.c
 *
 *  written:       1991 06 25
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link_up ()
{
  eval_logic_link (aw, "up");
}

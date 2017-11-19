/*
 *  FILE ~/usr/ned/08/ned0855.c
 *
 *  written:       1991 06 25
 *  latest update: 1994-04-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link_prev ()
{
  eval_logic_link (aw, "prev");
}

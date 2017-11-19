/*
 *  FILE ~/usr/ned/08/ned0854f.c
 *
 *  written:       1994-05-15
 *  latest update: 1994-05-15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link_sort ()
{
  eval_logic_link (aw, "sort");
}

/*
 *  FILE ~/usr/ned/08/ned0854g.c
 *
 *  written:       1994-05-15
 *  latest update: 1995-06-24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link_view ()
{
  eval_logic_link (aw, "view");
}

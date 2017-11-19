/*
 *  FILE %ned/08/ned0854a.c
 *
 *  written:       1991 06 25
 *  latest update: 1996-05-25 10:43:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link_next ()
{
  eval_logic_link (aw, "next");
}

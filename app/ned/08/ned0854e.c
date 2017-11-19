/*
 *  FILE ~/usr/ned/08/ned0874.c
 *
 *  written:       1991 09 27
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
void p_logic_link_lang ()
{
  eval_logic_link (aw, "lang");
}

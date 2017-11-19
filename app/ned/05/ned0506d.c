/*
 *  FILE %ned/05/ned0506d.c
 *
 *  Zeilennummer der aktuellen Zeile berechnen
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:25:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_cnt_act_line ()
{
  aw->znr= ned_cnt_line_2beg (aw->WC_act);
}

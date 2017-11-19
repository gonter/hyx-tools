/*
 *  FILE %ned/05/ned0508t.c
 *
 *  jump to current line, place current line onto top of screen
 *
 *  written:       1997-01-06
 *  latest update: 1997-06-11 14:50:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_jmp_aktline_top ()
{
  ned_w_jmp_aktline (aw, NEDJMP_LINE_TOP, 0, NEDJMP_FLAG_STD);
}

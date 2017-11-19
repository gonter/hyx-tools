/*
 *  FILE %ned/05/ned0508m.c
 *
 *  jump to current line, place current line onto bottom of the screen
 *
 *  written:       1997-01-06
 *  latest update: 1997-06-11 14:49:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_jmp_aktline_bot ()
{
  ned_w_jmp_aktline (aw, NEDJMP_LINE_BOT, 0, NEDJMP_FLAG_STD);
}

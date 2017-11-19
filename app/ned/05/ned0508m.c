/*
 *  FILE %ned/05/ned0508m.c
 *
 *  jump to current line, place current line into mid-screen
 *
 *  written:       1996-12-19
 *  latest update: 1997-06-11 14:49:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_jmp_aktline_mid ()
{
  ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_STD);
}

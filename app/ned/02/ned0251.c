/*
 *  FILE %ned/02/ned0251.c
 *
 *  vi emulation: insert after line
 *
 *  written:       1996-02-03
 *  latest update: 1996-05-17  1:09:59
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_substitute ()
{
  vi_change_text (aw, VI_CHG_CHAR, 1);
}

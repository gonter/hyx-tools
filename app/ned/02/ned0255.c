/*
 *  FILE %ned/02/ned0255.c
 *
 *  change to end of line
 *
 *  written:       1996-05-23
 *  latest update: 1996-10-05 10:40:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_change_line ()
{
  vi_change_text (aw, VI_CHG_LINE, 1);
  set_repeat_command ((void *) 0);
}

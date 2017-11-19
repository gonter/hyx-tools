/*
 *  FILE %ned/02/ned0254b.c
 *
 *  change to begin of line
 *
 *  written:       1996-10-05
 *  latest update: 1996-10-05 10:41:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_change_2boln ()
{
  vi_change_text (aw, VI_CHG_2BOLN, 1);
  set_repeat_command ((void *) 0);
}

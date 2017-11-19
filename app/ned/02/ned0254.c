/*
 *  FILE %ned/02/ned0254.c
 *
 *  change to end of line
 *
 *  written:       1996-05-23
 *  latest update: 1996-05-23 12:21:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_change_2eoln ()
{
  vi_change_text (aw, VI_CHG_2EOLN, 1);
  set_repeat_command ((void *) 0);
}

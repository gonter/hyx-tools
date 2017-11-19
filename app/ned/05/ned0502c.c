/*
 *  FILE %ned/05/ned0502c.c
 *
 *  delete from the cursor position to the begin of the line
 *  WS: ??
 *  VI: d^
 *
 *  written:       1996-10-05
 *  latest update: 1996-10-05  9:22:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_del2boln ()
{
  set_repeat_command (ned_del2boln);
  ned_w_del2boln (aw, 1);
}

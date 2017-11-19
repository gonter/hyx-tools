/*
 *  FILE %ned/05/ned0502.c
 *
 *  delete from the cursor position to the end of the line
 *  WS: ^QY
 *  VI: D, d$
 *
 *  written:       1987 04 08
 *  latest update: 1996-10-05  9:22:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_del2eoln ()
{
  set_repeat_command (ned_del2eoln);
  /********* ned_w_del2eoln (aw); T2D: Test; OLD 1996-10-05 10:47:40 */
  ned_w_del2boln (aw, 2);
}

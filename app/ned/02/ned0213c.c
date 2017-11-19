/*
 *  FILE %ned/02/ned0213c.c
 *
 *  Bildschirmaufbau
 *  -  resize one ore more windows
 *
 *  written:       1987 04 08
 *                 1994-08-20: isolated from ned0213b.c
 *  latest update: 1997-10-26 10:54:11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void q2_wdwsize (struct WINDOWCTRL *w, int pos)
{
  ned_window_size (w, pos, 1);
  ned_w_jmp_aktline (w, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
}

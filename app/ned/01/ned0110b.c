/*
 *  FILE %ned/01/ned0110b.c
 *
 *  half page up
 *
 *  written:       1996-05-23
 *  latest update: 1996-07-21 19:12:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_half_page_up ()
{
  ned_w_page_up (aw, 1);
}

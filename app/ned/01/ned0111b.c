/*
 *  FILE %ned/01/ned0111b.c
 *
 *  half page down
 *
 *  written:       1996-05-23
 *  latest update: 1996-07-21 19:12:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_half_page_down ()
{
  ned_w_page_down (aw, 1);
}

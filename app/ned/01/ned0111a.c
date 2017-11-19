/*
 *  FILE %ned/01/ned0111a.c
 *
 *  page down
 *
 *  written:       1996-05-23
 *  latest update: 1996-05-23 13:44:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_page_down ()
{
  ned_w_page_down (aw, 0);
}

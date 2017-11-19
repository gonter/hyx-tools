/*
 *  FILE %ned/01/ned0110a.c
 *
 *  page up
 *
 *  written:       1996-05-23
 *  latest update: 1999-05-02  4:31:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_page_up ()
{
  ned_w_page_up (aw, 0);
}

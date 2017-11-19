/*
 *  FILE %ned/01/ned0106p.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1997-08-28
 *  latest update: 1997-08-28 10:38:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int repeat;

/* ------------------------------------------------------------------------ */
void ned_cursor_right ()
{
  ned_w_cursor_right (aw, REPEAT);
}

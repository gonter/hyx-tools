/*
 *  FILE %ned/01/ned0105p.c
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
void ned_cursor_left ()
{
  ned_w_cursor_left (aw, REPEAT);
}

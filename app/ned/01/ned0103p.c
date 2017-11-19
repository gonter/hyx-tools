/*
 *  FILE %ned/01/ned0103p.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1996-12-19
 *  latest update: 1997-08-28  0:29:08
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
void ned_cursor_down ()
{
  ned_w_cursor_down (aw, REPEAT);
}

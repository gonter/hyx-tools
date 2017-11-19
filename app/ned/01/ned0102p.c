/*
 *  FILE %ned/01/ned0102p.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1996-12-19
 *  latest update: 1997-08-28  0:40:43
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
void ned_cursor_up ()
{
  ned_w_cursor_up (aw, REPEAT);
}

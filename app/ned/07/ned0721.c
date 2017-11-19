/*
 *  FILE %ned/07/ned0721.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *  latest update: 1996-05-26  9:35:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int blk;

/* ------------------------------------------------------------------------ */
void ned_blk_screen ()
{
  blk= 1;
  ned_display_window (aw);
}

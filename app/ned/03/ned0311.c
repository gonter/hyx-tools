/*
 *  FILE %ned/03/ned0311.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1996-03-16  1:37:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_backcolnxt ()
{
  int color;

  color= (aw->attr_text & 0x70) >> 4;
  color= ((color + 1) << 4) & 0x70;
  aw->attr_text= (aw->attr_text & 0x8F) | color;
  aw->w_upd |= 0x04;
  ned_display_window (aw);
}

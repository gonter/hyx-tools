/*
 *  FILE %ned/03/ned0310.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1996-03-16  1:36:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_colornxt ()
{
  int color;

  color= (aw->attr_text + 1) & 0x0F;
  aw->attr_text= (aw->attr_text & 0xF0) | color;
  aw->w_upd |= 0x04;
  ned_display_window (aw);
}

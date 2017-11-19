/*
 *  FILE %ned/06/ned0602.c
 *
 *  Refresh Screen
 *
 *  written:       1994-05-23: isolated from ned0604.c
 *  latest update: 2000-08-25 19:29:47
 *  $Id: ned0602.c,v 1.2 2000/08/25 18:05:48 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int akt_buttons;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_clear_screen ()
{
  w_cls ();
  show_buttons (aw);
  restore_message_line ();
}

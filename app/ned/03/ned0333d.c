/*
 *  FILE %ned/03/ned0333d.c
 *
 *  written:       1995-10-22
 *  latest update: 1998-08-16 12:26:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_show_tag ()
{
  ned_save_reload (aw, WCTDM_show_tag);
  ned_message_1 ("turned tag display on");
}

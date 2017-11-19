/*
 *  FILE %ned/03/ned0333c.c
 *
 *  written:       1995-10-22
 *  latest update: 1998-08-16 12:26:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_show_tag_normally ()
{
  ned_save_reload (aw, WCTDM_normal);
  ned_message_1 ("turned tag display off");
}

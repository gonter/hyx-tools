/*
 *  FILE %ned/03/ned0333e.c
 *
 *  written:       1995-10-22
 *  latest update: 1999-05-01 15:03:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_show_full_tag ()
{
  ned_save_reload (aw, WCTDM_show_full_tag);
  ned_message_1 ("turned tag display on");
}

/* ------------------------------------------------------------------------ */
void ned_reload_ascii ()
{
  ned_save_reload (aw, WCTDM_ASCII);
  ned_message_1 ("turned tag display on");
}

/* ------------------------------------------------------------------------ */
void ned_reload_sgml ()
{
  ned_save_reload (aw, WCTDM_SGML);
  ned_message_1 ("turned tag display on");
}

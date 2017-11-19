/*
 *  FILE %ned/04/ned0411.c
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1997-01-12 16:04:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "message.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct WINDOWCTRL *windows;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_abandon ()               /* ^K Q: Abandon File at curr. Window       */
{
  if (oper_level >= LEV_FIO) return;

  if (aw->first != (struct LINE *) 0)
  {
    if (aw->f_upd)
      if (get_confirmation (CNF_abandon, 0) <= 0) return;

    ned_wc_abandon (aw);
  }

  if (windows->next == (struct WINDOWCTRL *) 0) p_exit ();
  else ned_close_window ();
}

/*
 *  FILE %ned/04/ned0409c.c
 *
 *  save the current file after possibly renaming it
 *
 *  This is used to emulate PICO's stupid exit command.
 *
 *  written:       1996-05-27
 *  latest update: 1997-01-12 16:04:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include "message.h"

extern struct WINDOWCTRL *aw, *windows;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_pico_exit ()
{
  int do_save= 0;
  int rv;

  if (oper_level < LEV_FIO
      && aw->file_or_frame != (void *) 0
      && aw->f_upd
     )
  {
    if ((rv= get_confirmation (CNF_pico_exit, -1)) == 0)
    {
      ned_wc_abandon (aw);
      if (windows->next == (struct WINDOWCTRL *) 0) p_exit ();
      else ned_close_window ();
    }
    else if (rv == 1)
    {
      do_save= (ned_rename_object () > 0);
    }
  }

  if (do_save) p_ssave ();
}

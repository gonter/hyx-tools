/*
 *  FILE %ned/03/ned0314.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *                 1991 05 29: revision
 *  latest update: 2001-02-11 12:55:49
 *  $Id: ned0314.c,v 1.2 2001/02/12 00:03:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"
#include "message.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_fget ()         /* ^K G: Get File */
{
  if (oper_level >= LEV_FNM) return;

  if (aw->f_upd)
  {
    if (get_confirmation (CNF_old_version, 0) <= 0) return;
    aw->f_upd= 0;
  }

  s_fget (aw);
  ned_display_window (aw);
}

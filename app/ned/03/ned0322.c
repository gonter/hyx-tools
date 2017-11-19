/*
 *  FILE %ned/03/ned0322.c
 *
 *  Text to DOS: Einschalten des 0x0D Flags im ganzen File
 *
 *  written:       1990 11 04
 *                 1991 01 29: Revision
 *  latest update: 1996-07-26  3:34:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_line_end_MSDOS ()
{
  register struct LINE *l1, *l2;

  if (aw == (struct WINDOWCTRL *) 0
      || (l1= l2= aw->WC_act) == (struct LINE *) 0
      || (aw->WC_edit_mode & EDIT_READ_ONLY)
     ) return;

  aw->bin_eoln= 0x0A;

  while (l1 != (struct LINE *) 0)
  {
    l1->line_flg |= LINE_CODE_0x0D;
    l1= l1->prev;
  }

  while (l2 != (struct LINE *) 0)
  {
    l2->line_flg |= LINE_CODE_0x0D;
    l2= l2->next;
  }

  aw->f_upd= 1;
}

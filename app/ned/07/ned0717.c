/*
 *  FILE %ned/07/ned0717.c
 *
 *  loesche die Block-Markierungen aus den Zeilen
 *
 *  written:       1987 04 08
 *  latest update: 1997-09-28 10:24:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_reset_block_flags (struct WINDOWCTRL *w)
{
  register struct LINE *p;

  if (w == (struct WINDOWCTRL *) 0
      || (p= ned_find_first_line (w->WC_first)) == (struct LINE *) 0
     )
    return -1;

  for (; p != (struct LINE *) 0; p= p->next)
    p->line_flg &= LINE_BLOCK_CLR;

  return 1;
}

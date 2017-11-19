/*
 *  FILE %ned/05/ned0503.c
 *
 *  written:       1996-07-07
 *  latest update: 1999-04-25 16:31:06
 *  $Id: ned0503b.c,v 1.5 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_cb_jump_to_line (const char *str, void *cb_data)
{
  struct WINDOWCTRL *wc;
  int lnr;

  if ((wc= (struct WINDOWCTRL *) cb_data) != (struct WINDOWCTRL *) 0
      && str != (char *) 0
     )
  {
    lnr= (int) get_parameter_value (str);
    ned_jmp_2line_by_nr (wc, lnr, 3);
    aw= wc;                     /* T2D: change aw only if focused ...       */
  }

  return 0;
}

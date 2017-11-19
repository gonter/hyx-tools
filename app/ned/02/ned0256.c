/*
 *  FILE %ned/02/ned0256.c
 *
 *  vi emulation: place cursor at begin of line
 *
 *  written:       1996-05-23
 *  latest udpate: 2001-02-11 11:35:58 added vi_wc_jmp_boln
 *  $Id: ned0256.c,v 1.2 2001/02/12 00:03:25 gonter Exp $
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_jmp_boln ()
{
  vi_wc_jmp_boln (aw);
}

/* ------------------------------------------------------------------------ */
void vi_wc_jmp_boln (struct WINDOWCTRL *wc)
{
  int ch;

  ned_w_jmp_in_line (wc, NEDJMP_BOLN, 0);

  if (wc != (struct WINDOWCTRL *) 0
      && ((ch= get_txt (wc->WC_act, 0)) == ' '
          || ch == '\t'
         )
     )
    ned_wc_word_lr (wc, JMPWRD_right_beg_2);
}

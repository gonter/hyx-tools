/*
 *  FILE %ned/03/ned0301.c
 *
 *  Toggle Insert/Overwrite Mode
 *
 *  written:       1987 04 08
 *  latest update: 1996-02-16 10:22:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_ovins ()
{
  ned_wc_ins_mode (aw,
    (aw->ins_flg == INSFLG_insert) ? INSFLG_overwrite : INSFLG_insert);
}

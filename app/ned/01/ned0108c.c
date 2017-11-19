/*
 *  FILE %ned/01/ned0108c.c
 *
 *  written:       1996-05-23
 *  latest update: 2001-02-11 11:50:53
 *  $Id: ned0108c.c,v 1.2 2001/02/12 00:03:21 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* Um ein Wort nach links bzw. rechts springen ---------------------------- */
void p_word_right_beg_2 () { ned_wc_word_lr (aw, JMPWRD_right_beg_2); }

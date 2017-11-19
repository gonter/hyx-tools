/*
 *  FILE %ned/01/ned0108d.c
 *
 *  written:       1996-05-23
 *  latest update: 2001-02-11 11:50:35
 *  $Id: ned0108d.c,v 1.2 2001/02/12 00:03:22 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* Um ein Wort nach links bzw. rechts springen ---------------------------- */
void p_word_right_end_2 () { ned_wc_word_lr (aw, JMPWRD_right_end_2); }

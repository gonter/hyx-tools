/*
 *  FILE %ned/01/ned0108b.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1994-08-20
 *  latest update: 2001-02-11 11:51:25
 *  $Id: ned0108b.c,v 1.2 2001/02/12 00:03:21 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* Um ein Wort nach links bzw. rechts springen ---------------------------- */
void p_word_right_end () { ned_wc_word_lr (aw, JMPWRD_right_end); }

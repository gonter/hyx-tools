/*
 *  FILE %ned/01/ned0107.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen:
 *  Word Left
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 2001-02-11 11:52:06
 *  $Id: ned0107.c,v 1.2 2001/02/12 00:03:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* Um ein Wort nach links bzw. rechts springen ---------------------------- */
void p_word_left  () { ned_wc_word_lr (aw, JMPWRD_left_beg); }

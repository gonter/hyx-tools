/*
 *  FILE %ned/01/ned0108a.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 2001-02-11 11:51:30
 *  $Id: ned0108a.c,v 1.2 2001/02/12 00:03:21 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* Um ein Wort nach links bzw. rechts springen ---------------------------- */
void p_word_right_beg () { ned_wc_word_lr (aw, JMPWRD_right_beg); }

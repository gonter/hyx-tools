/*
 *  FILE %ned/01/ned0112.c
 *
 *  Aktivierung von Sub-Kommando Prozessoren
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1996-07-27 10:55:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
void p_ctrlq ()         /* Quick Operationen */
{
  pfx= P_CTRLQ;
}

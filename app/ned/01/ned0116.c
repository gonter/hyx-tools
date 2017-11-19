/*
 *  FILE ~/usr/ned/01/ned0116.c
 *
 *  Aktivierung von Sub-Kommando Prozessoren
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
void p_funct ()         /* Funktionstasten */
{
  pfx= P_FUNCT;
}

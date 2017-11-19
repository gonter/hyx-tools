/*
 *  FILE ~/usr/ned/01/ned0114.c
 *
 *  Aktivierung von Sub-Kommando Prozessoren
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1994-12-26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
void p_ctrlo ()         /* Screen and Window Operationen */
{
  pfx= P_CTRLO;
}

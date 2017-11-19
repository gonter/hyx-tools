/*
 *  FILE %ned/01/ned0113.c
 *
 *  Aktivierung von Sub-Kommando Prozessoren
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1996-05-08 19:51:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
void p_ctrlk ()         /* Block & File Operationen */
{
  pfx= P_CTRLK;
}

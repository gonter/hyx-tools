/*
 *  FILE %ned/04/ned0409.c
 *
 *  save the current file
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1996-12-29 22:04:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_save ()
{
  if (oper_level < LEV_FIO) ned_w_save (aw, 1);
}

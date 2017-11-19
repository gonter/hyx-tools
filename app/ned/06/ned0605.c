/*
 *  FILE %ned/06/ned0605.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:25:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern struct WINDOWCTRL *aw;
extern int akt_page;
extern int oper_level;
extern int key;
extern int COL_STATUS;

/* ------------------------------------------------------------------------ */
void p_jmpwdw ()       /* ^O 1..9 */
{
  if (oper_level >= LEV_WDW) return;
  if (key <= '0' || key > '9') return;

  w_setstring (akt_page, aw->ax+4, aw->ay-1, aw->ax+7, aw->ay-1,
               COL_STATUS, "    ", 0x01);

  q_jmpwdw (key-'0');
}

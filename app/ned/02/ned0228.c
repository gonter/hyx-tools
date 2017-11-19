/*
 *  FILE %ned/02/ned0228.c
 *
 *  Ausgabe einer Zahl als Window Nummer
 *
 *  written:       1987 04 08
 *                 1990 01 28: Revision
 *                 1991 02 03: Revision
 *  latest update: 1995-09-30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
void wd_show_wdnr (
int p,                  /* Window Page          */
int x,                  /* Window AX            */
int y,                  /* Window AY            */
int c,                  /* Color                */
int n)                  /* Number to Display    */
{
  w_setchar (p, x  , y, c, ' ');
  w_setchar (p, x+1, y, c, (n> 9)?(n/10)+'0':' ');
  w_setchar (p, x+2, y, c, (n%10)+'0');
  w_setchar (p, x+3, y, c, ' ');
}

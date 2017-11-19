/*
 *  FILE ~/usr/win/1/win_0123.c
 *
 *  written:       1994-08-20
 *  latest update: 1994-08-20
 *
 */

#include <stdio.h>
#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void w_print_long (int p, int x, int y, int c, char *fmt, long val)
{
  char vals [48];
  sprintf (vals, fmt, val);
  w_prntcol (p, x, y, c, vals);
}

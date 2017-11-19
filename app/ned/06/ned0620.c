/*
 *  FILE ~/usr/ned/06/ned0620.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *  latest update: 1994-04-02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int COL_ASK;

/* ------------------------------------------------------------------------ */
void debug (char *s)
{
  w_setstring (0, 0, 1, 79, 24, COL_ASK, s, 0x01);
}

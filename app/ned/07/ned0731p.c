/*
 *  FILE %ned/07/ned0731p.c
 *
 *  Print a Block
 *
 *  written:       1992 01 23
 *  latest update: 1996-05-26 12:25:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_blk_print ()                       /* print block */
{
  q_wablk (2);
}

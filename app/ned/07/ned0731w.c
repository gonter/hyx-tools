/*
 *  FILE %ned/07/ned0731w.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1991 05 17
 *  latest update: 1996-05-26 12:24:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_blk_write ()                       /* Write Block to File   */
{
  q_wablk (0);
}

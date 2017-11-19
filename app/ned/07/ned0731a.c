/*
 *  FILE %ned/07/ned0731a.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1991 05 17
 *  latest update: 1996-05-26 12:25:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_blk_append ()                       /* Append Block to File   */
{
  q_wablk (1);
}

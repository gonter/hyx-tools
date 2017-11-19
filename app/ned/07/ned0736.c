/*
 *  FILE %ned/07/ned0736.c
 *
 *  jump to a marker
 *
 *  written:       1996-10-03
 *  latest update: 1996-10-20 17:19:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int key;                 /* last key pressed */

/* ------------------------------------------------------------------------ */
void ned_jmp_marker_key ()
{
  ned_jmp_marker (key, 0);
}

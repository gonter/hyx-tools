/*
 *  FILE %ned/07/ned0737.c
 *
 *  jump to marker number 1
 *
 *  written:       1996-10-03
 *  latest update: 1996-11-03 18:52:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_jmp_marker_1 ()
{
  ned_jmp_marker ('1', 0);
}

/* ------------------------------------------------------------------------ */
void ned_jmp_marker_find ()
{
  ned_jmp_marker ('/', 0);
}

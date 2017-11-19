/*
 *  FILE ~/usr/ned/11/ned1109.c
 *
 *  written:       1992 01 02
 *  latest update: 1994-05-23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_find_lower_bracket ()
{
  ned_find_bracket (3);
}

/*
 *  FILE %ned/11/ned1108.c
 *
 *  written:       1992 01 02
 *  latest update: 1996-12-29 17:06:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_find_higher_bracket ()
{
  ned_find_bracket (2);
}

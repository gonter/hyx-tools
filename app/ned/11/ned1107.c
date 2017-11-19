/*
 *  FILE %ned/11/ned1107.c
 *
 *  written:       1991 02 02
 *                 1991 12 31: revision and bug fix
 *  latest update: 1996-12-29 17:06:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_find_matching_bracket ()
{
  ned_find_bracket (1);
}

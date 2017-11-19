/*
 *  FILE %ned/03/ned0316.c
 *
 *  ALT-=: Eingabe eines doppelten Querstriches (Character 205, 0xCD)
 *
 *  written:       1989 12 16
 *                 1991 01 29: Revision
 *  latest update: 1997-01-19  0:51:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_alt_gleich ()
{
#ifdef MSDOS
  q_insert (0xCD, 1);
#endif
}

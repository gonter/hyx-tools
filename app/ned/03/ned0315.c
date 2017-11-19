/*
 *  FILE %ned/03/ned0315.c
 *
 *  ALT--: Eingabe eines einfachen Querstriches (Character 196, 0xC4)
 *
 *  written:       1989 12 16
 *                 1991 01 29: Revision
 *  latest update: 1997-01-19  0:50:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_alt_minus ()
{
#ifdef MSDOS
  q_insert (0xC4, 1);
#endif
}

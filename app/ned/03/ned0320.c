/*
 *  FILE %ned/03/ned0320.c
 *
 *  ALT-Z: Eingabe eines NULL-Characters (Character 0, 0x00)
 *
 *  written:       1989 12 16
 *                 1991 01 29: Revision
 *  latest update: 1997-01-05 12:06:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_alt_zero ()
{
  ned_insert_special_char ('0');
}

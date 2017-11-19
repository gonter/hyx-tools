/*
 *  FILE %ned/06/ned0619.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *  latest update: 1995-11-12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_ultra_panic ()
{
  exit (0);
}

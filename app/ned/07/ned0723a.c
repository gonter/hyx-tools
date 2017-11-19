/*
 *  FILE %ned/07/ned0723a.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1997-03-31
 *  latest update: 1997-03-31 12:31:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_drop_buffer (int name)
{
  return ned_drop_buffer2 (ned_get_buffer (name, 0));
}

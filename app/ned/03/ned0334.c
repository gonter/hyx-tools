/*
 *  FILE %ned/03/ned0334.c
 *
 *  ALT-`: enter an entity string and insert it as a character
 *
 *  written:       1994-05-30
 *  latest update: 1996-10-05 11:47:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
void ned_read_entity ()
{
#define BULEN 40
  char bu [BULEN];

  bu [0]= 0;
  if (rd_str ("Entity: ", bu, BULEN) == -1) return;
  ned_enter_entity (bu);
}

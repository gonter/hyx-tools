/*
 *  FILE %ned/04/ned0430.c
 *
 *  write extraction information to file
 *
 *  written:       1992 04 05
 *  latest update: 1996-03-17 11:08:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_extract ()
{
  char msg [80];

  msg [0]= 0;
  if (rd_str ("message: ", msg, 80) == -1) return;
  q_extract ("$$appl.msg", msg);
}

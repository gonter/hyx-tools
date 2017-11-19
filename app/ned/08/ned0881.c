/*
 *  FILE %ned/08/ned0881.c
 *
 *  *** NOT USED ***
 *
 *  written:       1991 10 24
 *  latest update: 1996-12-03 16:20:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_2cross_ref (char *str, int MAX_STR)
{
  str[0]= '$';
  str[1]= 0;

  if (rd_str ("search word: ", &str[1], MAX_STR-1) == -1) return;
  ned_activate_cross_ref (str, 1, CRF_IN_CRF, CRF_GLOBAL_AND_LOCAL);
}

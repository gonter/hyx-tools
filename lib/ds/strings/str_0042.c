/*
 *  FILE %ds/strings/str_0042.c
 *
 *  Wichtungscodes fuer den IBM PC (MSDOS)
 *
 *  written:       1990 11 23
 *                 1993-01-02: include table
 *  latest update: 1995-12-25
 *
 */

#include <gg/strings.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static int IBMPC_WEIGHT_CODES [256] =
{
#include "str_0042.tbl"
} ;

/* ------------------------------------------------------------------------ */
int get_weight_code (int ch)
{
  return IBMPC_WEIGHT_CODES [ch & 0x00FF];
}

/* ------------------------------------------------------------------------ */
void set_weight_code (int ch, int code)
{
  IBMPC_WEIGHT_CODES [ch & 0x00FF] = code;
}

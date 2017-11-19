/*
 *  FILE %ds/strings/str_0041.c
 *
 *  Character Code Categories fÅr den IBM PC (MSDOS)
 *
 *  written:       1990 11 10
 *                 1993-01-02: include table
 *  latest update: 1995-12-25
 *
 */

#include <gg/strings.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static unsigned char IBMPC_CATEGORY_CODES [256] =
{
#include "str_0041.tbl"
} ;

/* ------------------------------------------------------------------------ */
int get_cat_code (int ch)
{
  return IBMPC_CATEGORY_CODES [ch & 0x00FF];
}

/* ------------------------------------------------------------------------ */
void set_cat_code (int ch, int code)
{
  IBMPC_CATEGORY_CODES [ch & 0x00FF] = (unsigned char) code;
}

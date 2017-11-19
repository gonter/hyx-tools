/*
 *  FILE %ned/09/ned0976.c
 *
 *  submit a macro string
 *
 *  written:       1994-02-06
 *  latest update: 1996-07-11 18:32:32
 *  $Id: ned0976.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_submit_macro (const char *s)
{
  int mac_siz;
#ifdef MSDOS
#define CMD_SIZE 76
#else
#define CMD_SIZE 1024
#endif
  char token [CMD_SIZE+2];

  /* TCL_MACROS: an alternative function should submit a tcl function.      */
  /* see: NED tcl macros for more information about this stuff.             */

  mac_siz= trans_str (s, token, CMD_SIZE);
  mac_undef (MACRO_SUBMIT);
  mac_define (MACRO_SUBMIT, MPt_key_sequence, token, mac_siz);
  p_macro (MACRO_SUBMIT);

  return 0;
}

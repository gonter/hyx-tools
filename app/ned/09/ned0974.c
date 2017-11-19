/*
 *  FILE %ned/09/ned0974.c
 *
 *  Makroprozessor
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1999-04-25 16:36:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
int mac_undef (int num)
{
  struct NED_MACRO *mp;

  if (num < 0 || num >= N_MACRO
      || ned_main_context == (struct NED_CONTEXT *) 0
      || (mp= ned_main_context->NED_macro_table [num])
         == (struct NED_MACRO *) 0
     ) return -1;

  free_or_what (mp->NED_mac_contents);
  free (mp);
  ned_main_context->NED_macro_table [num]= (struct NED_MACRO *) 0;

  return 0;
}

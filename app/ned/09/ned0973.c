/*
 *  FILE %ned/09/ned0973.c
 *
 *  clear out all macros from the table
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1999-04-25 16:35:38
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
int mac_clr ()
{
  struct NED_MACRO *mp;
  int i;

  if (ned_main_context == (struct NED_CONTEXT *) 0) return -1;

  for (i= 0; i < N_MACRO; i++)
  {
    if ((mp= ned_main_context->NED_macro_table [i])
         != (struct NED_MACRO *) 0
       )
    {
      free_or_what (mp->NED_mac_contents);
      free (mp);
      ned_main_context->NED_macro_table [i]= (struct NED_MACRO *) 0;
    }
  }

  return 0;
}

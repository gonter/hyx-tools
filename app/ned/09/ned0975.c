/*
 *  FILE %ned/09/ned0975.c
 *
 *  makroprocessor: transfer a string into the macro buffer
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1999-04-25 16:36:10
 *  $Id: ned0975.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
int mac_define (int num, int macro_type, const char *str, int lng)
{
  struct NED_MACRO *mp;

  if (num < 0 || num >= N_MACRO
      || lng <= 0
      || ned_main_context == (struct NED_CONTEXT *) 0
     ) return -1;

  if ((mp= ned_main_context->NED_macro_table [num]) == (struct NED_MACRO *) 0)
  { /* macro position not defined yet, do it now... */
    if ((mp= (struct NED_MACRO *) calloc (sizeof (struct NED_MACRO), 1))
        == (struct NED_MACRO *) 0) return -1;

    ned_main_context->NED_macro_table [num]= mp;
  }

  /* drop old contents, if any */
  free_or_what (mp->NED_mac_contents);

  /* setup new contents */
  mp->NED_mac_contents= strdup (str);
  mp->NED_mac_type= macro_type;

  return 0;
}

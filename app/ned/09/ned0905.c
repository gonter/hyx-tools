/*
 *  FILE %ned/09/ned0905.c
 *
 *  ** OBSOLETE **
 *
 *  Setup File processing
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1997-10-26 11:13:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int stp_whatprim (char *s)
{
  int i;

#ifdef __OBSOLETE__ /* 1996-11-10  9:59:42 */
  for (i= 0; i < N_PRIMS; i++)
      if (strcmp (CT1 [i], s) == 0)
         return i;
#endif /* __OBSOLETE__ 1996-11-10  9:59:42 */

  return -1;
}

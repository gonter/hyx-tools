/*
 *  FILE ~/usr/ned/01/ned0135.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:29:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *wdw_alloc ()
{
  return (struct WINDOWCTRL *) calloc (sizeof (struct WINDOWCTRL), 1);
}

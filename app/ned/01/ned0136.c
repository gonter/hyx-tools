/*
 *  FILE ~/usr/ned/01/ned0136.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:29:23
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
struct FILECTRL *file_alloc ()
{
  return (struct FILECTRL *) calloc (sizeof (struct FILECTRL), 1);
}

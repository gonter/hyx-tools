/*
 *  FILE %ned/01/ned0131.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *  latest update: 1999-04-25 16:29:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef MSDOS
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct LINE *alloc_line ()
{
  return (struct LINE *) calloc (sizeof (struct LINE), 1);
}

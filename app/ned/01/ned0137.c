/*
 *  FILE %ned/01/ned0137.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:29:26
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
struct FEATURE *ned_feature_alloc ()
{
  return (struct FEATURE *) calloc (sizeof (struct FEATURE), 1);
}

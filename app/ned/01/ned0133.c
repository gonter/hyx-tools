/*
 *  FILE ~/usr/ned/01/ned0133.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:27:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct TXT *tx_alloc (int size)     /* Laenge des gewuenschten Textsegments */
{
  return txch_alloc (size, 0);
}


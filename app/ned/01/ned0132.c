/*
 *  FILE %ned/01/ned0132.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1999-04-25 16:29:15
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
struct TXT *txch_alloc (int size, int ch)
{
  register struct TXT *tx;

  if (size > 255
      || (tx= (struct TXT *) malloc (sizeof (struct TXT)-3 + size))
          == (struct TXT *) 0
     ) return (struct TXT *) 0;

  tx->t_lng= (unsigned char) size;
  strfill (tx->t, size, ch);
  tx->next= (struct TXT *) 0;

  return tx;
}

/*
 *  FILE %ned/01/ned0140.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:29:34
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
void tx_free (register struct TXT *tp)  /* Textsegmente freigeben           */
{
  register struct TXT *tp2;

  while (tp != (struct TXT *) 0)
  {
    tp2= tp->next;
    free (tp);
    tp= tp2;
  }
}

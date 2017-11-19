/*
 *  FILE %ned/03/ned0308.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1989 11 12: nicht mehr abhaengig von TXT_LNG
 *                 1991 01 29: Revision
 *  latest update: 1996-07-26  3:35:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int get_txt (
struct LINE *lp,                /* Zeile, in der gesucht werden soll        */
int coln)                       /* Spalten Nummer: 0..32000                 */
{
  struct TXT *tx;

  if (lp == (struct LINE *) 0
      || lp->lng <= coln
      || (tx= lp->txt) == (struct TXT *) 0
         /* Error: Zeile enthaelt keinen Text, obwohl lp->lng >= coln ist  */
     )
    return -1;

  if (coln < 0) return '>';

  for (;;)
  {
    if (coln < tx->t_lng)
      return tx->t [coln] & 0x00FF;     /* gesuchtes Zeichen                */

    coln -= tx->t_lng & 0x00FF;
    if ((tx= tx->next) == (struct TXT *) 0)
      return -1;                        /* Error: Text Segment fehlt        */
  }

  return -1;
}

/* ------------------------------------------------------------------------ */
int get_txt_visible (
struct LINE *lp,                /* Zeile, in der gesucht werden soll        */
int coln)                       /* Spalten Nummer: 0..32000                 */
{
  int ch;

  return ((ch= get_txt (lp, coln)) == -1) ? ' ' : ch;
}

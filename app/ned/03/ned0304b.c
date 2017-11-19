/*
 *  FILE %ned/03/ned0304b.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1996-06-09
 *  latest update: 1996-11-03 20:57:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void q_insert_string (
char *s,                /* character to insert                              */
int  df)                /* display flag: 1 -> display line after inserting  */
{
  int k;

  if (s == (char *) 0) return;

  while ((k= *s++) != 0) q_insert (k, df);
}

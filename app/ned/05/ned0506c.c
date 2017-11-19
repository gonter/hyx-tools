/*
 *  FILE %ned/05/ned0506b.c
 *
 *  Zahl aller Zeilen in einen Window ermitteln
 *
 *  written:       1991 06 01
 *  latest update: 1996-05-26 11:34:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* Zeilennummer einer Zeile berechnen: ------------------------------------ */
int ned_cnt_total_lines (struct LINE *a)
{
  int cnt;

  cnt= ned_cnt_line_2beg (a) + ned_cnt_line_2end (a);

  return (cnt > 0) ? cnt-1 : 0;
}

/*
 *  FILE ~/usr/sbr/dt024.c
 *
 *  operations with date and time
 *
 *  written:       1988 03 28: (as datum.c)
 *                 1991 06 24: revision
 *                 1994-05-07: revision: split up in more modules
 *  latest update: 1994-07-23
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* Differenz zwischen 2 Tagen: -------------------------------------------- */
int delta_datum (
int bjahr,      /* first day */
int bmon,
int btag,
long *v1,
int  *t1,
int ejahr,      /* last day */
int emon,
int etag,
long *v2,       /* Datumswert */
int *t2,        /* Wochentag  */
int *d,
int *e)         /* error code: 0 .. ok; 1 .. error in date 1; 2 .. @d2 */
{
  int sj;

  *e= 1;
  if (valid_datum (bjahr, bmon, btag, v1, t1, &sj, &sj) == -1) return -1;

  *e= 2;
  if (valid_datum (ejahr, emon, etag, v2, t2, &sj, &sj) == -1) return -1;

  if (((long) *v2) < ((long) *v1)) return -1;
  *d= (int) (((long) *v2) - ((long) *v1));
  *e= 0;

  return 0;
}

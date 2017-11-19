/*
 *  FILE ~/usr/sbr/dt021.c
 *
 *  operations with date and time
 *
 *  written:       1988 03 28: (as datum.c)
 *                 1991 06 24: revision
 *  latest update: 1994-05-07: revision: split up in more modules
 *
 */

#include <stdio.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int chk_datum (
char *sb,       /* String: Beginn-Datum; Format JJJJ-MM-TT                  */
char *se,       /* .       Ende  -Datum                                     */
int sl,         /* max. String-Laenge  (nicht ausgewertet!!!)               */
int *d,         /* Dauer in Tagen zw. Beginn und Ende                       */
int *e,         /* Fehler Code: 0 .. ok;                                    */
                /*              1 .. Beginn, 2 .. Ende  falsch              */
int *beg_jahr)  /* 1. Jahr, falls identifiziert                             */
/* RETURN: -1 .. Fehler; 0 .. korrekte Daten                                */
{
  int ib= 0;
  int ie= 0;
  int bjahr, bmon, btag;
  int ejahr, emon, etag;
  long v1, v2;
  int  t1, t2;

  while (sb [ib] == ' ') ib++;
  while (se [ie] == ' ') ie++;
  if (sb [ib] == ':')
     { sscanf (& sb [ib+1], "%d", d);
       return 0;
     }
  if (se [ie] == ':')
     { sscanf (& se [ib+1], "%d", d);
       return 0;
     }
  if (get_datum (sb, ib, sl, &bjahr, &bmon, &btag) == -1)
     { *e = 1;
       return -1;
     }
  if (get_datum (se, ie, sl, &ejahr, &emon, &etag) == -1)
     { *e = 2;
       return -1;
     }
  if (bjahr < 100) bjahr += 1900;
  if (ejahr < 100) ejahr += 1900;
  if (delta_datum (bjahr, bmon, btag, &v1, &t1,
                   ejahr, emon, etag, &v2, &t2, d, e) == -1)
     return -1;
/*  w_setcup (0,0,3);
    printf ("BEGINN: %4d-%2d-%2d -> %ld %d\n",
          bjahr, bmon, btag, v1, t1);
  printf ("ENDE:   %4d-%2d-%2d -> %ld %d\n",
          ejahr, emon, etag, v2, t2); */
  (*d)++;
  *beg_jahr= bjahr;

  return 0;
}

/*
 *  FILE %ds/cal/dt025.c
 *
 *  operations with date and time
 *
 *  written:       1988 03 28: (as datum.c)
 *                 1991 06 24: revision
 *                 1994-05-07: revision: split up in more modules
 *  latest update: 1997-09-03 18:06:17
 *  $Id: dt025.c,v 1.2 2010/05/03 23:43:28 gonter Exp $
 *
 */

#include <gg/dates.h>
#include <stdio.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* Datum moeglich: (32. Dezember ... ) ------------------------------------ */
int valid_datum (
int jahr,
int mon,
int tag,
long *v,               /* Datumswert                    */
int *t,                /* Wochentag                     */
int *xsj,              /* 1 -> Schaltjahr               */
int *xt)               /* Zahl der Tage in diesem Monat */
{
  int sj = 0;
  long   x1, x2, x3;
  double y1, y2;
  long vv;

  if (tag  <    1 ||
      mon  <    1 || mon  >   12)   return -1;
  if ((jahr % 4) == 0)
     if ((jahr % 100) == 0)
          if ((jahr % 400) == 0)
                       sj = 1;
          else         sj = 0;
     else              sj = 1;
  else                 sj = 0;

  *xsj= sj;

  switch (mon)
  {
    case  1: case  3: case  5: case  7:
    case  8: case 10: case 12:
             if (tag > (*xt = 31)) return -1;
             break;
    case  4: case  6: case  9:
    case 11: if (tag > (*xt = 30)) return -1;
             break;
    case  2: if (sj)
                { if (tag > (*xt = 29)) return -1;
                }
             else if (tag > (*xt = 28)) return -1;
             break;
  }

  x1 = (long) ((long) 365 * (long) jahr) +
       (long) tag + (long) (31*(mon-1));

  if (mon == 1 || mon == 2)
       { x2 = (long)   ((jahr-1)/100+1);
         y1 = (double) (((double) (x2*(long)3))/4.0);
         x3 = (long)   ((jahr-1)/4);
         vv = x1 + x3;
         vv = vv - ((long) y1);
/* printf ("%ld; x1=%ld x2=%ld x3=%ld y1=%g          \n",
        vv, x1, x2, x3, y1); */
       }
  else { x2 = (long)   (jahr/100+1);
         y1 = (double) (((double) (x2*(long)3))/4.0);
         x3 = (long)   (jahr/4);
         y2 =          ((double) mon) * 0.4 + 2.3;
         vv = x1 + x3;
         vv = vv - ((long) y1);
         vv = vv - ((long) y2);
/* printf ("%ld; x1=%ld x2=%ld x3=%ld y1=%g y2=%g\n",
        vv, x1, x2, x3, y1, y2); */
       }

  x1= vv - ( (-vv)/(long) 7)* (long) 7;
  /*** *t= (int) (x1 % 7); ***/
  *t= (int) (vv % 7);
  *v= vv;
  printf ("x1=%ld t=%ld v=%ld\n", (long) x1, (long) *t, (long) *v);

  return 0;
}

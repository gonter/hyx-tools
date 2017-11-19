/*
 *  FILE %ds/cal/dt034.c
 *
 *  return month and day of easter
 *  see: calendar.hyx
 *
 *  written:       1995-06-25
 *  latest update: 1995-10-23
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int get_easter (int year, int *month, int *day)
{
  int A, B, C, D, E, F, G, H, I, K, L, M, N, P;

  A= year%19;
  B= year/100;
  C= year%100;

  if (year <= 1583)
  {
    D= (19*A+15)%30;
    E= (D+C+C/4-B)%7;
  }
  else
  {
    D= B/4;
    E= B%4;
  }

  F= (B+8)/25;
  G= (B-F+1)/3;
  H= (19*A+B-D-G+15)%30;
  I= C/4;
  K= C%4;
  L= (2*E-H+2*I-K+32)%7;
  M= (A+11*H+22*L)/451;
  N= (H+L-7*M+114)/31;
  P= (H+L-7*M+114)%31;

  *month= N;
  *day= P+1;

#ifdef DEBUG
  printf ("A=%2d B=%2d C=%2d D=%2d E=%2d F=%2d G=%2d\n", A, B, C, D, E, F, G);
  printf ("H=%2d I=%2d K=%2d L=%2d M=%2d N=%2d P=%2d\n", H, I, K, L, M, N, P);
  printf ("year=%d month=%d day=%d\n", year, *month, *day);
#endif

  return 0;
}

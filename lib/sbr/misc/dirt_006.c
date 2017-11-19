/*
 *  FILE ~/usr/sbr/dirt_006.c
 *
 *  written:       1989 11 04
 *  latest update: 1994-06-01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>

#define char_or_dot(x)  (((x) >= 0x20 && (x) <= 0x7e) ? (x) : '.')

/* ------------------------------------------------------------------------ */
void dump (FILE *fo, char *x, int cnt)
{
  int i;
  int b;
  int off= 0;

  for (; cnt > 0; cnt -= 16)
  {
    b= (cnt > 16) ? 16 : cnt;
    fprintf (fo, "%04X: ", off);
    for (i=0; i<  b; i++) fprintf (fo, "%02X ", x[i] & 0x00FF);
    for (   ; i< 16; i++) fprintf (fo, "   ");
    for (i=0; i<  b; i++) fprintf (fo, "%c", char_or_dot (x[i]));
    fprintf (fo, "\n");
    x= &x[16];
    off += 16;
  }
}

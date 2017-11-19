/*
 *  FILE ~/usr/sbr/dirt_008.c
 *
 *  written:       1990 04 13
 *  latest update: 1994-12-11
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void flip_int (char *v)
{
  int x;

  x= v[0];
     v[0]= v[1];
           v[1]= x;
}

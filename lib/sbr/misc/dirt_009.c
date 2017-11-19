/*
 *  FILE ~/usr/sbr/dirt_009.c
 *
 *  written:       1990 04 13
 *  latest update: 1995-02-12
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void flip_long (char *v)
{
  int x;

  x = v[0];
      v[0] =               v[3];
                           v[3] = x;

  x =        v[1];
             v[1] = v[2];
                    v[2] =        x;
}

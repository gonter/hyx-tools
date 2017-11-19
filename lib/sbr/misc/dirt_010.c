/*
 *  FILE /usr/sbr/dirt_010.c
 *
 *  1990 04 13
 */

# pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void flip_long_2 (char *v)
{
  int x;

  x = v[0];
      v[0] =        v[2];
                    v[2] =        x;

  x =        v[1];
             v[1] =        v[3];
                           v[3] = x;
}

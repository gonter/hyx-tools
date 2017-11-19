/*
 *  FILE /usr/sbr/dirt_003.c
 *
 *  1989 11 04
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
get_patch (char *p, char *s)
{
  int i;

  for (i = 0; i < 5; i++) *s++ = *p++;
}


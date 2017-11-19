/*
 *  FILE /usr/sbr/dirt_002.c
 *
 *  1989 11 04
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void patch_str (char *p, char *s)
{
  int i;
  for (i = 0; i < 5; i++) *p++ = *s++;
}


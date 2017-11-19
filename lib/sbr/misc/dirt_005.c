/*
 *  FILE /usr/sbr/dirt_005.c
 *
 *  1989 11 04
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void pokeb (char far *p, char b)
{
  *p = b;
}


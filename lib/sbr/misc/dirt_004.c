/*
 *  FILE /usr/sbr/dirt_004.c
 *
 *  1989 11 04
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
int peekb (char far *p)
{
  return *p & 0x00FF;
}

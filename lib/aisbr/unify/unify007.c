/*
 *  FILE ~/usr/aisbr/unify/unify007.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <stdio.h>
#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
int fs_mbq (char *s)
/* Return: 1 if string must be quoted for printing; 0 otherwise */
{
  int ch, i;

  for (i= 0; (ch= *s) != 0; s++,i++)
  {
    if ((ch < 'a' || ch > 'z')
      &&(ch < 'A' || ch > 'Z')
      && ch != '@'
      && ch != '_'
      &&(i == 0 || ch < '0' || ch > '9')) return 1;
  }
  return 0;
}

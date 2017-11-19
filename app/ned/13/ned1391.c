/*
 *  FILE %ned/13/ned1391.c
 *
 *  NED message handling for terminal programs
 *
 *  written:       1997-08-03
 *  latest update: 1999-04-25 16:36:58
 *  $Id: ned1391.c,v 1.3 2002/06/10 06:17:42 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include "ed.h"

static int show_level= 0;

/* ------------------------------------------------------------------------ */
int ned_message (
int cnt,
char *p1, char *p2, char *p3, char *p4, char *p5, char *p6)
{
  int i;
  char *s[6];

  if (show_level > 0) return 0;

  s [0]= p1;
  s [1]= p2;
  s [2]= p3;
  s [3]= p4;
  s [4]= p5;
  s [5]= p6;

  printf ("NOTE: ");
  for (i= 0; i < cnt; i++) printf (" %s ", s [i]);
  putchar ('\n');

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_error_message (char *s)
{
  printf ("ERROR: %s\n", s);

  return 0;
}

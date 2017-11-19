/*
 *  FILE %ned/05/ned0506a.c
 *
 *  get the line number of LINE b relativ to the window where
 *  LINE a is located.
 *
 *  first line := 1
 *  -1 if line
 *
 *  This function is used to verify if the line b is in the same
 *  window as line a.
 *
 *  written:       1996-07-11
 *  latest update: 1996-07-11 18:16:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* Zeilennummer einer Zeile berechnen: ------------------------------------ */
int ned_cnt_line_relative (register struct LINE *a, register struct LINE *b)
{
  register int lin= 1;
  register struct LINE *c;

  if (a == (struct LINE *) 0 || b == (struct LINE *) 0) return -1;

  for (; (c= a->prev) != (struct LINE *) 0; a= c);
  for (; a != (struct LINE *) 0; a= a->next)
  {
    if (a == b) return lin;
    lin++;
  }

  return -1;
}

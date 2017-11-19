/*
 *  FILE ~/usr/ned/06/ned0623.c
 *
 *  File- und Windowoperationen:
 *  Filename ueberpruefen und Datenstruktur anlegen
 *
 *  *** currently not used ***
 *
 *  written:       1991 03 10
 *  latest update: 1994-08-13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void correct_pathname (char *s)
{
  if (s == (char *) 0) return;
  for (; *s; s++)
    if (*s == '\\') *s= '/';
}

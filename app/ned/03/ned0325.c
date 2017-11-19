/*
 *  FILE ~/usr/ned/03/ned0325.c
 *
 *  NED_interpreter
 *
 *  written:       1990 01 20: aus Modul NED00.C isoliert
 *                 1991 01 29: Revision
 *  latest update: 1994-04-29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

void cdecl ret (void);
int (*cdecl PRIMITIVE_code []) (void);
extern int (* PRIMITIVE_code []) (void);
extern int    PRIMITIVE_size [];

/* ------------------------------------------------------------------------ */
void NEDa2_interpreter (char *IP)
{
  int dist;

  for (;;)
  {
    (*PRIMITIVE_code [*IP]) ();
    if ((dist = PRIMITIVE_size [*IP]) == 0) break;
    IP += dist;
  }
}

void ret (void) {}

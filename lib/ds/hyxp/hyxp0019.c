/*
 *  FILE ~/usr/ds/hyxp/hyxp0019.c
 *
 *  insert TEXT_ELEMENT list at given position
 *
 *  written:       1994-11-18
 *  latest update: 1995-03-30
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT **hyx_find_last_tx_elem_ptr (
struct TEXT_ELEMENT **d)
{
  if (d == (struct TEXT_ELEMENT **) 0)
    return (struct TEXT_ELEMENT **) 0;

  while (*d != (struct TEXT_ELEMENT *) 0)
  {
    d= &(*d)->TE_next;
  }

  return d;
}

/*
 *  FILE ~/usr/ds/hyxp/hyxp0018.c
 *
 *  insert TEXT_ELEMENT list at given position
 *
 *  written:       1991 04 07
 *  latest update: 1995-03-30
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_append_tx_elem_list (
struct TEXT_ELEMENT **d,                        /* destination              */
struct TEXT_ELEMENT *s)                         /* source                   */
{
  if (d == (struct TEXT_ELEMENT **) 0
      || s == (struct TEXT_ELEMENT *) 0) return (struct TEXT_ELEMENT *) 0;

  while (s != (struct TEXT_ELEMENT *) 0)
  {
    *d= s;
    d= &s->TE_next;
    if (s->TE_next == (struct TEXT_ELEMENT *) 0) return s;
    s= s->TE_next;
  }

  return (struct TEXT_ELEMENT *) 0;
}

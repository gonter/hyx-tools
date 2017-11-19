/*
 *  FILE %ned/07/ned0723.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1996-05-27
 *  latest update: 1997-07-27 12:07:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_drop_buffer2 (struct NED_BUFFER *bu)
{
  if (bu->l_beg != (struct LINE *) 0) ned_lines_free (bu->l_beg);

  bu->l_beg= bu->l_end= (struct LINE *) 0;

  return 0;
}

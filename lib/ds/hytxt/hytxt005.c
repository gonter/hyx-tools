/*
 *  FILE %ds/hytxt/hytxt005.c
 *
 *  Datenstruktur fuer HyperText Frame freigeben
 *
 *  written:       1990 04 12
 *  latest update: 1996-10-09 21:40:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
void free_HYTXT_FRAME (struct HYTXT_FRAME *fd)
{
  struct HYTXT_ATTR *a1, *a2;

  for (a1= fd->hytxt_attr; (a2= a1) != (struct HYTXT_ATTR *) 0;)
  {
    a1= a1->hytxt_attr_next;
    free (a2);
  }

  if (fd != (struct HYTXT_FRAME *) 0) free (fd->hytxt_frame_name);
  free (fd);
}

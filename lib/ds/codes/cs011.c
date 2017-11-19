/*
 *  File %ds/codes/cs011.c
 *
 *  written:       1996-02-24: g.gonter@ieee.org
 *  latest update: 1996-02-24 11:03:38
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_print_frames (FILE *fo, struct CS_record *recs)
{
  long c= 0L;

  for (; recs != (struct CS_record *) 0; recs= recs->CSr_next)
  {
    /* fprintf (fo, "record[%ld]:  count=%ld\n", ++c, recs->CSr_count); */
    cs_print_frame (fo, recs->CSr_fields);
  }

  return c;
}

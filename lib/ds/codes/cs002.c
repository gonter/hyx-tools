/*
 *  File %ds/codes/cs002.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1996-02-24 10:53:45
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_print_records (FILE *fo, struct CS_record *recs)
{
  long c= 0L;

  for (; recs != (struct CS_record *) 0; recs= recs->CSr_next)
  {
    fprintf (fo, "record[%ld]:  count=%ld\n", ++c, recs->CSr_count);
    cs_print_fields (fo, recs->CSr_fields);
  }

  return c;
}

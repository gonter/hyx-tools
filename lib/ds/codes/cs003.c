/*
 *  File %ds/codes/cs003.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1996-02-24 11:02:26
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_print_fields (FILE *fo, struct CS_field *fields)
{
  long c= 0L;

  for (; fields != (struct CS_field *) 0; fields= fields->CSf_next)
  {
    fprintf (fo, "  field[%ld]:", ++c);
    fprintf (fo, "  name=\'%s\'  type=%ld",
       fields->CSf_name, fields->CSf_type);
    if (fields->CSf_type == CSft_number)
      fprintf (fo, "  number=0x%04lX", fields->CSf_number);
    if (fields->CSf_type == CSft_string)
      fprintf (fo, "  string=\'%s\'", fields->CSf_string);
    fputc ('\n', fo);
  }

  return c;
}

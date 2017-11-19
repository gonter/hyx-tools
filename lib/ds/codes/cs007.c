/*
 *  File %dpp/codes/cs007.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <string.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
struct CS_field *cs_find_field (
struct CS_record *first,
char *f1_name,
int   f1_type,
char *f1_string,
long  f1_number,
char *f2_name)
{
  struct CS_field *fld0;
  struct CS_field *fld1;
  struct CS_field *fld2;

  if (f1_name == (char *) 0 || *f1_name == 0
      || f2_name == (char *) 0 || *f2_name == 0
     ) return (struct CS_field *) 0;

  for (; first != (struct CS_record *) 0; first= first->CSr_next)
  {
    fld1= fld2= (struct CS_field *) 0;

    for (fld0  = first->CSr_fields;
         fld0 != (struct CS_field *) 0;
         fld0  = fld0->CSf_next)
    {
      if (strcmp (fld0->CSf_name, f1_name) == 0
        && fld0->CSf_type == f1_type
        && ((f1_type == CSft_string)
            ? (strcmp (fld0->CSf_string, f1_string) == 0)
            : (fld0->CSf_number == f1_number)))           fld1= fld0;
      if (strcmp (fld0->CSf_name, f2_name) == 0)          fld2= fld0;
    }

    if (fld1 != (struct CS_field *) 0
      &&fld2 != (struct CS_field *) 0) return fld2;
  }

  return (struct CS_field *) 0;
}

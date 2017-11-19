/*
 *  FILE %ds/dbx/dbx_0001.c
 *
 *  database processing
 *
 *  written:       1996-11-26
 *  latest update: 1996-11-26 17:53:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/dbx.h>

/* ------------------------------------------------------------------------ */
struct DBX_SCHEMA *dbx_new_schema (
int n_fields,
char *name)
{
  struct DBX_SCHEMA *schema;
  int size;

  size= sizeof (struct DBX_SCHEMA)
        + (n_fields-2)*(sizeof (struct DBX_FIELD_DESCRIPTOR *));

printf (">> schema: n_fields=%d size=%d\n", n_fields, size);

  if ((schema= (struct DBX_SCHEMA *) calloc (size, 1))
               != (struct DBX_SCHEMA *) 0)
  {
    schema->n_fields= n_fields;
    schema->name= (name == (char *) 0) ? (char *) 0 : strdup (name);
  }

  return schema;
}

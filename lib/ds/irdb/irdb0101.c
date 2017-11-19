/*
 *  FILE %ds/irdb/irdb0101.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-28 11:41:30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_diag (
FILE *fo,
struct IRDB_HANDLE *handle)
{
  long rc= 0L;
  long ty;

  if (fo == (FILE *) 0) return -1L;
  if (handle == (struct IRDB_HANDLE *) 0) return 0L;
  ty= handle->IRDB_type;

  fputs ("\n*************************************************\n[101] ", fo);
#ifdef IRDB_USE_CLASS_NAME
  fputs ("class_name=", fo);
  irdb_diag_string (fo, handle->IRDB_class_name);
  fputc ('\n', fo);
#endif /* IRDB_USE_CLASS_NAME */

  fprintf (fo, "type=%s", irdb_type (ty));
  if (ty == (long) IRDBty_struct || ty == (long) IRDBty_array)
    fprintf (fo, " of %s", irdb_type (handle->IRDB_payload_type));
  fputc ('\n', fo);

  irdb_diag_payload (fo, handle, 2);

  /* write structure's header */
  fprintf (fo, "pl_size=%ld\n", handle->IRDB_payload_size);
  fputs ("*************************************************\n\n", fo);

  return rc;
}

/*
 *  FILE %ds/irdb/irdb0102.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 17:10:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_diag_to_stream (FILE *fo, struct IRDB_HANDLE *handle, int indent)
{
  long ty;

  if (fo == (FILE *) 0) return -1L;
  if (handle == (struct IRDB_HANDLE *) 0) return 0L;

  ty= handle->IRDB_type;
  /* write structure's header, part 1 */
  blanks (fo, indent);
  fprintf (fo, "[102] type=%s", irdb_type (ty));
  if (ty == (long) IRDBty_struct || ty == (long) IRDBty_array)
    fprintf (fo, " of %s", irdb_type (handle->IRDB_payload_type));
  fputc ('\n', fo);

  /* first dump the payload, then dump the header! */
  irdb_diag_payload (fo, handle, indent+2);

  /* write structure's header; part 2 */
  blanks (fo, indent);
  fprintf (fo, "size=%ld\n", handle->IRDB_payload_size);

#ifdef IRDB_USE_CLASS_NAME
  blanks (fo, indent);
  fputs ("class_name=", fo);
  irdb_diag_string (fo, handle->IRDB_class_name);
  fputc ('\n', fo);
#endif /* IRDB_USE_CLASS_NAME */

  return 0L;
}

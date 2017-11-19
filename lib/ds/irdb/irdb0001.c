/*
 *  FILE %ds/irdb/irdb0001.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-05-07 13:41:45
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_dump_to_file (
char *filename,
struct IRDB_HANDLE *handle)
{
  FILE *fo;
  long rc= 0L;

  if ((fo= fopen (filename, "wb")) == (FILE *) 0) return -1L;
  if (handle == (struct IRDB_HANDLE *) 0) return 0L;

  /* write structure's header */
  dpp_fwrite_long (fo, handle->IRDB_type, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_size, 4);
  dpp_fwrite_long (fo, 0x123489ABL, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_type, 4);

#ifdef IRDB_USE_CLASS_NAME
  irdb_dump_string (fo, handle->IRDB_class_name);
#endif /* IRDB_USE_CLASS_NAME */

  irdb_dump_payload (fo, handle);
  fclose (fo);

  irdb_fixup_pos_header (filename, handle);

  return rc;
}

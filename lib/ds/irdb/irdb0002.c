/*
 *  FILE %ds/irdb/irdb0002.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-04-27 14:07:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_dump_to_stream (FILE *fo, struct IRDB_HANDLE *handle)
{
  long pos;

  if (fo == (FILE *) 0) return -1L;
  if (handle == (struct IRDB_HANDLE *) 0) return 0L;

  /* first dump the payload, then dump the header! */
  irdb_dump_payload (fo, handle);

  /* write structure's header */
  pos= ftell (fo);
  dpp_fwrite_long (fo, handle->IRDB_type, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_size, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_type, 4);

#ifdef IRDB_USE_CLASS_NAME
  irdb_dump_string (fo, handle->IRDB_class_name);
#endif /* IRDB_USE_CLASS_NAME */

  return pos;
}

/*
 *  FILE %ds/irdb/irdb0001.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-04-05 11:23:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_fixup_pos_header (
char *filename,
struct IRDB_HANDLE *handle)
{
  FILE *fo;

  /* fixup header information */
  if ((fo= fopen (filename, "r+b")) == (FILE *) 0) return -1L;
printf ("fixing header: size=0x%08lX position=0x%08lX\n",
handle->IRDB_payload_size, handle->IRDB_payload);

  dpp_fwrite_long (fo, handle->IRDB_type, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_size, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload, 4);
  dpp_fwrite_long (fo, handle->IRDB_payload_type, 4);
  fclose (fo);

  return 0L;
}

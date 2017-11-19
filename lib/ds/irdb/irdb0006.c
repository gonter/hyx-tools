/*
 *  FILE %ds/irdb/irdb0006.c
 *
 *  irrelational database
 *  - commit changes to disk file
 *
 *  written:       1996-04-27
 *  latest update: 1996-04-28 12:11:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_commit (struct IRDB_POS *pos)
{
  struct IRDB_HANDLE *handle;
  FILE *fo;

  if (pos == (struct IRDB_POS *) 0
      || (handle= pos->IRDB_handle) == (struct IRDB_HANDLE *) 0
     ) return -1L;

  irdb_get_pos_file_pointer (pos, IRDBom_closed);

  if (pos->IRDB_is_new)
  {
    irdb_dump_to_file (pos->IRDB_file_name, handle);
    pos->IRDB_is_new= 0; /* the POS is not new anymore now ... */
  }
  else
  {
    if ((fo= fopen (pos->IRDB_file_name, "ab")) == (FILE *) 0)
      return -1L;

    irdb_dump_payload (fo, handle);
    fclose (fo);
    irdb_fixup_pos_header (pos->IRDB_file_name, handle);
  }

  return 0L;
}

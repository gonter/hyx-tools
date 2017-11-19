/*
 *  FILE %ds/irdb/irdb0103.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-27 12:51:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_diag_payload (
FILE *fo,
struct IRDB_HANDLE *handle,
int indent)
{
  long rc= 0L;
  long pos= 0L;
  long size;
  struct YTREE *yt;
#define BUFFER_SIZE 256

  if (fo == (FILE *) 0) return -1L;

  if (handle == (struct IRDB_HANDLE *) 0) goto DONE;

  blanks (fo, indent);
  fprintf (fo, "[103] type=%s", irdb_type (handle->IRDB_type));

  switch ((int) handle->IRDB_type)
  {
    case IRDBty_int:
      fprintf (fo, " val=0x%08lX\n", handle->IRDB_payload);
      handle->IRDB_payload_size= 4;
      break;

    case IRDBty_string:
      fputs (" val=", fo);
      size= irdb_diag_string (fo, (char *) handle->IRDB_payload);
      handle->IRDB_payload_size= size;
      break;

    case IRDBty_struct:
      yt= (struct YTREE *) handle->IRDB_payload;

      fprintf (fo, " of %s\n", irdb_type (handle->IRDB_payload_type));

      {
        char *buffer= (char *) 0;
        struct IRDB_DUMP dmp;

        if ((buffer= malloc (BUFFER_SIZE)) == (char *) 0) goto DONE;
        dmp.fo= fo;
        dmp.type= handle->IRDB_payload_type;
        dmp.indent= indent+2;

        ytree_track (yt,
                     buffer, BUFFER_SIZE, 0,
                     irdb_diag_struct, (void *) &dmp);
        free_or_what (buffer);
      }
      break;

    case IRDBty_struct_dumped:
      fprintf (fo, " of %s", irdb_type (handle->IRDB_payload_type));

    case IRDBty_string_dumped:
    case IRDBty_array_dumped:
    case IRDBty_block_dumped:
      fprintf (fo, " dumped at 0x%08lX, size=%ld\n",
               handle->IRDB_payload,
               handle->IRDB_payload_size);
      break;

    case IRDBty_float:
    case IRDBty_block:
    case IRDBty_array:
    default:
      fputs (" T2D!\n", fo);
      break;
  }

DONE:
  return pos;
}

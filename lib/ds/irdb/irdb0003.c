/*
 *  FILE %ds/irdb/irdb0003.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-04-27 14:10:17
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
long irdb_dump_payload (
FILE *fo,
struct IRDB_HANDLE *handle)
{
  long rc= 0L;
  long pos= 0L;
  long size;
  long ty;
  char *cp;
  struct YTREE *yt;
  struct IRDB_DUMP dmp;
#define BUFFER_SIZE 256

  if (fo == (FILE *) 0) return -1L;

  if (handle == (struct IRDB_HANDLE *) 0) goto DONE;

#ifdef DEBUG2
printf ("irdb0003: cln='%s' type=%s\n",
#ifdef IRDB_USE_CLASS_NAME
handle->IRDB_class_name,
#else
"anon",
#endif /* !IRDB_USE_CLASS_NAME */
irdb_type (handle->IRDB_type));
#endif /* DEBUG2 */

  switch ((int) handle->IRDB_type)
  {
    case IRDBty_int:
      dpp_fwrite_long (fo, handle->IRDB_payload, 4);
      handle->IRDB_payload_size= 4;
      break;

    case IRDBty_string:
      pos= ftell (fo);
      cp= (char *) handle->IRDB_payload;
      size= irdb_dump_string (fo, cp);
      free_or_what (cp);

      handle->IRDB_payload_size= size;
      handle->IRDB_payload= pos;
      handle->IRDB_type= IRDBty_string_dumped;
      break;

    case IRDBty_float:
    case IRDBty_block:
    case IRDBty_array:
      fprintf (stderr, "irdb0003: T2D!\n");
      break;

    case IRDBty_struct:
      yt= (struct YTREE *) handle->IRDB_payload;

#ifdef DEBUG2
printf ("irdb0003: struct; payload_type=%s\n",
irdb_type (handle->IRDB_payload_type));
#endif /* DEBUG2 */

      if ((ty= handle->IRDB_payload_type) != IRDBty_int)
      {
        char *buffer= (char *) 0;

        if ((buffer= malloc (BUFFER_SIZE)) == (char *) 0) goto DONE;
        dmp.fo= fo;
        dmp.type= ty;

        ytree_track (yt,
                     buffer, BUFFER_SIZE, 0,
                     irdb_dump_struct, (void *) &dmp);
        free_or_what (buffer);

        handle->IRDB_payload_type= irdb_dumped_form (ty);
      }

      pos= ftell (fo);
      size= ytree_size (yt);
      ytree_dump (fo, yt);
      ytree_free (yt);

      handle->IRDB_payload_size= size;
      handle->IRDB_payload= pos;
      handle->IRDB_type= IRDBty_struct_dumped;

#ifdef DEBUG2
printf ("irdb0003: ytree position for '%s' at 0x%08lX, size=0x%04lX\n",
#ifdef IRDB_USE_CLASS_NAME
handle->IRDB_class_name,
#else
"anon",
#endif /* !IRDB_USE_CLASS_NAME */
pos, size);
#endif /* DEBUG2 */
      break;
  }

DONE:
  return pos;
}

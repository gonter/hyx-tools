/*
 *  FILE %ds/hyxdb/hyxdb005.c
 *
 *  hyxdb: HYX Database Management
 *  load a object from a frame
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 13:01:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
struct HYXDB_OBJECT *hyxdb_parse_stream (
struct HYXDB_CONTROL *ctrl,
FILE *fi,
long size,
char *frame_name)
{
  struct HYXDB_OBJECT *obj= (struct HYXDB_OBJECT *) 0;
  struct HYXDB_VALUE *value;
  char *buffer;
#define N_FIELDS 2
  char *fields [N_FIELDS];
  char *vs;
  int buffer_size;
  int rc;
  int n_fields;

  if (feof (fi)
      || (obj= hyxdb_new_object (ctrl, frame_name, 0L))
               == (struct HYXDB_OBJECT *) 0
     )
    return (struct HYXDB_OBJECT *) 0;

  if ((buffer= ctrl->buffer) == (char *) 0)
  {
    buffer= ctrl->buffer= malloc (ctrl->buffer_size= HYXDB_BUFFER_SIZE);
  }
  else buffer_size= ctrl->buffer_size;

  if (buffer == (char *) 0) return (struct HYXDB_OBJECT *) 0;

  while (size > 0L)
  {
    rc= fread_line (fi, buffer, buffer_size);
    if (rc <= 0 && feof (fi)) break;

    if (buffer [0] == '#'
        || strncmp ("<Frame ",  buffer, 7) == 0
        || strncmp ("</Frame>", buffer, 8) == 0
        || strncmp ("<hyx.f ",  buffer, 7) == 0
        || strncmp ("</hyx.f>", buffer, 8) == 0
       )
     continue;

    n_fields= split_string (buffer, '=', fields, N_FIELDS);

    if (n_fields != 2
        || (vs= fields [1]) == (char *) 0
        || *vs == 0
        || (value= hyxdb_new_value (HYXDB_string, vs, (long) strlen (vs)))
                     == (struct HYXDB_VALUE *) 0
       ) continue;

    hyxdb_insert_attribute (obj, fields [0], value, HYXDB_insert);
  }

  return obj;
}

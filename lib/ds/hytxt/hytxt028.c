/*
 *  FILE %ds/hytxt/hytxt028.c
 *
 *  written:       1994-12-11
 *  latest update: 1996-10-09 21:27:54
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
static char *buffer= (char *) 0;
static int buffer_size= 0;

/* ------------------------------------------------------------------------ */
int hyx_setup_segment (
struct FILE_SEGMENT **app_segments,
struct FILE_SEGMENT **fs_new,
char *x_line,
long *index_number)
{
  struct FILE_SEGMENT *fs;
  int xl;
#define N_FIELDS 4
  char *fields [N_FIELDS];
  int cnt_fields;
  long f_beg;
  long f_end;
  long f_siz;

  if ((xl= strlen (x_line)) > buffer_size)
  {
    if (buffer != (char *) 0) free (buffer);
    buffer= malloc (xl+1);
    buffer_size= xl;
  }

  if (buffer == (char *) 0) return -1;
  strcpy (buffer, x_line);
  cnt_fields= split_string (buffer, ';', fields, N_FIELDS);

  if (cnt_fields < 4) return -1;
  f_beg= (strcmp (fields [0], "-") == 0)
         ? 0L : get_parameter_value (fields [0]);
  f_end= (strcmp (fields [1], "-") == 0)
         ? 0x7FFFFFFEL : get_parameter_value (fields [0]);
  f_siz= f_end - f_beg +1L;

printf ("hyx_setup_segment: file=%s\n", fields [2]);
printf ("hyx_setup_segment: frame=%s\n", fields [3]);
printf ("hyx_setup_segment: begin=0x%08lX size=0x%08lX\n", f_beg, f_siz);

  if ((fs= hyx_make_segment (app_segments, fields [2], fields [3],
             index_number, FSop_update, f_beg, f_siz))
      == (struct FILE_SEGMENT *) 0) return -1;

  *fs_new= fs;

  return 0;
}

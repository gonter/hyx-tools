/*
 *  FILE %ds/streams/stre_f01.c
 *
 *  file stream operations
 *
 *  written:       1996-11-04
 *  latest update: 1996-11-04  0:10:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#define STREAM_FILE
#include <gg/streams.h>

/* ------------------------------------------------------------------------ */
struct STREAM_OBJECT *new_stream_file_object (FILE *fi)
{
  struct STREAM_OBJECT *so= (struct STREAM_OBJECT *) 0;

  if (fi != (FILE *) 0
      && (so= new_stream_object ()) != (struct STREAM_OBJECT *) 0
     )
  {
    so->next_char= stream_file_next_char;
    so->is_end=    stream_file_eof;
    so->stream_cd= (void *) fi;
  }

  return so;
}

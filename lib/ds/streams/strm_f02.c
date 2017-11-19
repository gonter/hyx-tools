/*
 *  FILE %ds/streams/stre_f02.c
 *
 *  file stream operations
 *
 *  written:       1996-11-04
 *  latest update: 1997-01-15 10:32:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#define STREAM_FILE
#include <gg/streams.h>

/* ------------------------------------------------------------------------ */
int stream_file_next_char (void *sop)
{
  FILE *fi;
  struct STREAM_OBJECT *so;

  if ((so= (struct STREAM_OBJECT *) sop) == (struct STREAM_OBJECT *) 0
      || (fi= (FILE *) so->stream_cd) == (FILE *) 0
     ) return -1;

  so->position++;
  return fgetc (fi) & 0x00FF;
}

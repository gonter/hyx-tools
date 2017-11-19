/*
 *  FILE %ds/streams/stre_f03.c
 *
 *  file stream operations
 *
 *  written:       1996-11-04
 *  latest update: 1997-01-15 10:34:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#define STREAM_FILE
#include <gg/streams.h>

/* ------------------------------------------------------------------------ */
int stream_file_eof (void *sop)
{
  FILE *fi;
  struct STREAM_OBJECT *so;

  return ((so= (struct STREAM_OBJECT *) sop) == (struct STREAM_OBJECT *) 0
          || (fi= (FILE *) so->stream_cd) == (FILE *) 0
          || feof (fi)
         ) ? 1 : 0;
}

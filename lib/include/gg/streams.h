/*
 *  include FILE <gg/streams.h>
 *
 *  methods
 *  data structures
 *  constants
 *  prototypes
 *  sub types: STREAM_FILE
 *
 *  written:       1996-11-04
 *  latest udpate: 1997-01-15 10:29:24
 *
 */

#ifndef __GG_streams__
#define __GG_streams__

#include <gg/floskel.h>

/* methods: --------------------------------------------------------------- */
typedef int STREAM_next_char (void *sop);
typedef int STREAM_end (void *sop);

/* data structures: ------------------------------------------------------- */
struct STREAM_OBJECT
{
  STREAM_next_char *next_char;
  STREAM_end *is_end;

  long position;
  void *stream_cd;
} ;

/* prototypes: ------------------------------------------------------------ */
#define new_stream_object() \
  ((struct STREAM_OBJECT *) calloc (sizeof (struct STREAM_OBJECT), 1))

#define stream_position(stream) (stream->position)

/* STREAM_FILE: ----------------------------------------------------------- */
#ifdef STREAM_FILE
struct STREAM_OBJECT *new_stream_file_object (FILE *fi);
int stream_file_next_char (void *sop);
int stream_file_eof (void *sop);
#endif /* STREAM_FILE */

#endif /* __GG_streams__ */

/*
 *  FILE ~/usr/lexicon/dict003.c
 *
 *  written:       1994-07-29
 *  latest update: 1995-08-19
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int write_lexicon_frame (
FILE *fhyx,                             /* file to write frame data to      */
char *frame_name,                       /* name used for the frame          */
struct TEXT_ELEMENT *lexicon_entry,     /* lexicon data structure           */
int write_nl)
{
  if (lexicon_entry == (struct TEXT_ELEMENT *) 0) return -1;

  /* fprintf (fhyx, "<:LX%08lX>", frame_index); */
  fprintf (fhyx, "<:%s>", frame_name);
  write_lexicon_text (fhyx, lexicon_entry, write_nl);
  fprintf (fhyx, "\n<;>");

  return 0;
}

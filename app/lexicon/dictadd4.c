/*
 *  FILE ~/usr/lexicon/dictadd4.c
 *
 *  write a complete lexicon entry
 *  source:      internal representation in memory
 *  destination: SGML formated representation
 *
 *  written:       1991 03 19
 *  latest update: 1995-08-19
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int write_lexicon_entry (
char *lexicon_file,
char *index_file,
long *frame_index,
char *frame_name,                       /* name used for the frame          */
struct TEXT_ELEMENT *lexicon_entry,     /* lexicon data structure           */
long *next_index,                       /* naechster moeglicher Index/File  */
int write_nl)                           /* 1 -> append LF after text        */
{
  FILE *fhyx;                   /* Lexicon File                             */
  long li_end;
  long li_begin;
  long li_cluster_number= 0L;

  if (*frame_index == 0L)
  {
    *frame_index= (*next_index)++;
    /*** printf ("setting frame_index to 0x%08lX\n", *frame_index); ***/
  }

  if (*frame_index < 0L) return 0;

  if ((fhyx= flopen (lexicon_file, "ab")) == (FILE *) 0)
  {
    fprintf (stdout, 
             "ERROR: dictadd4: file %s could not be appended\n",
             lexicon_file);
    return -1;
  }

  fseek (fhyx, 0L, 2);

  li_end=
  li_begin= ftell (fhyx);

  if (write_lexicon_frame (fhyx, frame_name, lexicon_entry, write_nl) != 0)
    return -1;

  li_end= ftell (fhyx) - 1L;
  fputc ('\n', fhyx);

  /* printf ("written: 0x%08lX '%s'\n", *frame_index, frame_name); */

  if (hyx_update_index (index_file, li_begin, li_end, li_cluster_number,
                        frame_index, next_index) != 0)
  {
    fprintf (stdout, 
             "ERROR: dictadd4: index could not be updated in file %s\n",
             index_file);
    return -1;
  }

  return 0;
}

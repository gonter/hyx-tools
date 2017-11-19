/*
 *  FILE %ds/hyxp/hyxp0024.c
 *
 *  read a lexicon entry
 *
 *  written:       1991 03 19
 *  latest update: 1996-02-18  8:32:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/parse.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_parse_hyx_frame_file (
struct HYX_PARSER_CLASS *hpc,
FILE *fhyx,                     /* Lexicon File                             */
FILE *fidx,                     /* Index File                               */
long frame_index,
struct TEXT_ELEMENT **lexicon_entry,
long end_tags [],
int num_end_tags)
/* Return:  0 ... OK; wenn *lexicon_entry == (char *) 0, dann existiert     */
/*                    kein Eintrag zum angegebenen Index (leerer Eintrag)   */
/*         -1 ... Error                                                     */
{
  long li_begin;                /* information from the index file          */
  long li_end;
  long li_cluster;
  long bytes_read;              /* number of bytes read from lexicon file   */

  *lexicon_entry= (struct TEXT_ELEMENT *) 0;

  if (deref_index (fidx, frame_index, &li_begin, &li_end, &li_cluster) != 0
      || li_begin <= 0L
     ) return -1;

  /* Lexicon Eintrag lesen */
  fseek (fhyx, li_begin, 0);
  if (hyx_parse1_file (hpc, fhyx, lexicon_entry, end_tags, num_end_tags,
                       li_end-li_begin+1L, &bytes_read) != 0)
  {
    fprintf (stdout, "WARNING: dictadd3: lexicon entry not read cleanly\n");
  }

  return 0;
}

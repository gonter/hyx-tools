/*
 *  FILE ~/usr/ds/hyxp/hyxp0023.c
 *
 *  read a lexicon entry
 *
 *  written:       1991 03 19
 *                 1995-01-23: renamed from dictadd3.c
 *  latest update: 1995-07-04
 *
 */


#include <stdio.h>
#include <gg/parse.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int hyx_parse_hyx_frame (
struct HYX_PARSER_CLASS *hpc,
char *lexicon_file,
char *index_file,
long frame_index,
struct TEXT_ELEMENT **lexicon_entry,
long end_tags [],
int num_end_tags)
/* Return:  0 ... OK; wenn *lexicon_entry == (char *) 0, dann existiert     */
/*                    kein Eintrag zum angegebenen Index (leerer Eintrag)   */
/*         -1 ... Error                                                     */
{
  FILE *fhyx;                   /* Lexicon File                             */
  FILE *fidx;                   /* Index File                               */
  char *fnm2open;

  if ((fidx= flopen (fnm2open= index_file, "rb")) == (FILE *) 0
     || (fhyx= flopen (fnm2open= lexicon_file, "rb")) == (FILE *) 0)
  {
    fprintf (stdout, 
             "ERROR: dict0031: file %s could not be opened\n",
             fnm2open);
    return -1;
  }

  return hyx_parse_hyx_frame_file (hpc, fhyx, fidx,
                                  frame_index, lexicon_entry,
                                  end_tags, num_end_tags);
}

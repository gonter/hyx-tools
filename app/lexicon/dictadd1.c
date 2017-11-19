/*
 *  FILE %lexicon/dictadd1.c
 *
 *  - info:
 *    Beschleunigung von Updates
 *
 *  written:       1991 03 17
 *  latest update: 2001-02-18 17:57:46
 *  $Id: dictadd1.c,v 1.4 2003/06/25 10:12:06 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>
#include <gg/parse.h>

#ifndef MSDOS
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
int dict_add_file (
struct HYX_PARSER_CLASS *hpc,
struct HYX_CLUSTER_CONTROL *hcc,
struct LEXICON_CONTROL *lcc,
char *fn,                       /* file to be processed                     */
int verbose_level)              /* to chat or not to chat ...               */
{
  FILE *fi;                     /* verarbeitetes Files                      */
  struct TEXT_ELEMENT *tx_new_entry= (struct TEXT_ELEMENT *) 0;
                                /* neu gelesener Eintrag                    */
  long record_counter= 0L;      /* number of used lexicon frames            */
  long chars_read;              /* number of chars read in lexicon entry    */
  int rc;

  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0
      || !hcc->HCC_dictadd1_inited
      || lcc == (struct LEXICON_CONTROL *) 0
     )
  {
    fprintf (stdout, "lexicon system not initialized!!!\n");
    return -1;
  }

  fputc ('\n', stdout);
  hyx_write_stamp (stdout, "pgm=dictadd");
  fprintf (stdout, "\nadding file %s in mode %d to lexicon\n",
           fn, hcc->HCC_dict_mode);
  fprintf (stdout, "frame name generation: %d\n", hcc->HCC_mode_frame_name);

  /****************
  fprintf (stdout, "head='%s' tail='%s'\n",
           lcc->LC_head_tag_str, lcc->LC_tail_tag_str);
  *****************/
  memory_statistics (stdout, 0L);

  if ((fi= (strcmp (fn, "$stdin") == 0 || strcmp (fn, "-") == 0)
      ? (FILE *) stdin : fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stdout, "dict_add_file: couldn't read from %s\n", fn);
    return 0;
  }
  printf ("dictadd1: reading file '%s'\n", fn);

  for (;;)
  {
    /* read entry from input file which shall be added to the lexicon */

#ifdef PARSER_DEBUG_B
  printf ("dictadd1: calling hyx_parse1_file () \n", fn);
#endif /* PARSER_DEBUG_B */

    rc= hyx_parse1_file (hpc, fi, &tx_new_entry,
                        lcc->LC_end_tags, lcc->LC_end_tag_count,
                        0x7FFFFFFFL, &chars_read);

    if (rc != 0 || chars_read == 0L)
    {
      fprintf (stdout,
               "note: hyx_parse_file: rc=%d chars_read=%ld fn=%s\n",
               rc, chars_read, fn);
      break;
    }

#ifdef PARSER_DEBUG_B
    printf ("dictadd1: calling dict_process_entry ()\n", fn);
#endif /* PARSER_DEBUG_B */

    rc= dict_process_entry (hpc, hcc, lcc, tx_new_entry,
                            (hyx_output_processor *) 0, (void *) 0,
                            verbose_level);
    if (rc == -1) break;
    if (rc == 1) continue;

    record_counter++;
    if ((record_counter % 0x00010000L) == 0)
      memory_statistics (stdout, record_counter);

    if (feof (fi)) break;
  }

  fprintf (stdout, "stopping...\n");

  if (strcmp (fn, "$stdin") != 0 && strcmp (fn, "-") != 0) fclose (fi);
  flclose_all ();
  memory_statistics (stdout, record_counter);

  return 0;
}

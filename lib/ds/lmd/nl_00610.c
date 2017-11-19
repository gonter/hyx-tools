/*
 *  FILE %nl_kr/lib/nl_00610.c
 *
 *  read and process a hypertext cluster
 *
 *  written:       1995-12-05
 *  latest update: 1995-12-05
 *  $Id: nl_00610.c,v 1.2 2001/10/08 15:01:26 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long lmd_read_hyx_cluster (
struct LMDC_CONTROL *lmdc,
char *fnm_hyx,
char *fnm_idx,
int *alphabet)
{
  long last_frame;              /* highest index in the hypertext clustr    */
  long frame_number;            /* current cluster number                   */
  long size;                    /* size of current frame                    */
  int rc;                       /* read count                               */
#define N_WORDS 80              /* maximum number of isolated words on line */
  char *words [N_WORDS];        /* isolated words                           */
  char *wrd;                    /* currently processed word                 */
  int wc;                       /* number of words actually isolated        */
  int word_number;              /* index of the currently processed word    */
  int word_length;              /* length of the currently processed word   */
  char docid_str [10];          /* document id as string, cluster number    */
  char *bu;                     /* line buffer                              */
  int MAX_STR;                  /* size of line buffer                      */
  int min_wordlength;
  int max_wordlength;
  long word_count= 0L;          /* overall total number of words processed  */
  long pos;                     /* filepointer position in cluster          */
  int first_line;               /* flag to indicate the first line in frame */

  FILE *fi_hyx= (FILE *) 0;
  FILE *fi_idx= (FILE *) 0;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (bu= lmdc->LMDC_buffer1) == (char *) 0
      || (last_frame= hyx_get_last_index (fnm_idx)) <= 0L
      || (fi_hyx= flopen (fnm_hyx, "rb")) == (FILE *) 0
      || (fi_idx= flopen (fnm_idx, "rb")) == (FILE *) 0
     )
    goto END;

  MAX_STR= lmdc->LMDC_buffer_size;
  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;

  for (frame_number= 1L; frame_number <= last_frame; frame_number++)
  {
    size= hyx_seek_by_index (fi_hyx, fi_idx, frame_number);

#ifdef __COMMENT__
1995-12-05 17:28:16
T2D, strategic desgin
Well, that is not really a nice way to treat a SGML file, but let us
start and change that stuff as soon as there is a need to change
it or the functions to do the dirty jobs are there....
#endif /* __COMMENT__ */

    long_to_hex (frame_number, docid_str);

    if (lmdc->LMDC_verbosity > 1)
      printf ("frame number: %s, size=%ld\n", docid_str, size);

    first_line= 1;
    while (size > 0L)
    {
      pos= ftell (fi_hyx);
      rc= fread_line (fi_hyx, bu, MAX_STR);
      if (rc <= 0 && feof (fi_hyx)) break;
      pos= ftell (fi_hyx) - pos;
      if (pos > size) bu [(int) size]= 0;
      size -= pos;

      if (first_line)
      {
#ifdef __COMMENT__
1995-12-05 20:46:25
T2D, tactical desgin
At this point we could record the frame name anywhere since it is
already right at our hands ...
#endif /* __COMMENT__ */
        if (lmdc->LMDC_verbosity > 1)
        {
          fputs (bu, stdout);
          fputc ('\n', stdout);
        }

        if (strstr (bu, "Frame $$index") != (char *) 0
            || strstr (bu, "Frame $$md5") != (char *) 0
           ) /* dont need that stuff... */
          break;

        first_line= 0;
      }

      wc= isolate2words (bu, words, N_WORDS, alphabet);
      if (wc > N_WORDS) wc= N_WORDS;

      for (word_number= 0; word_number < wc; word_number++)
      {
        wrd= words [word_number];
        to_lower (wrd);

/* OK, 1995-12-05 19:54:03 *************
printf ("word=%s", wrd);
***************************************/

        word_length= strlen (wrd);
        if (word_length < min_wordlength) continue;
        if (word_length > max_wordlength) wrd [max_wordlength]= 0;
        rc= lmd_idx (lmdc, wrd, frame_number, -1L, docid_str, 0, 0, 0L);
        if (rc == 0) word_count++;
/* printf ("  cnt=%ld\n", word_count); */
      }
    }
  }

  if (lmdc->LMDC_verbosity > 0)
    printf ("processed %ld frames from cluster '%s'\n", last_frame, fnm_hyx);

END:
  fclose_or_what (fi_hyx);
  fclose_or_what (fi_idx);

  return word_count;
}

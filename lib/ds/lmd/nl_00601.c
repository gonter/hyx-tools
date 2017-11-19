/*
 *  FILE %ds/lmd/nl_00601.c
 *
 *  read a cooked data stream for indexing
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 2001-02-04 21:05:19
 *  $Id: nl_00601.c,v 1.7 2001/10/08 15:01:26 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
static char *stream_commands [] =
{
  "DOCID",
  "DOCDEL",
  "DOCPTR",
  "STOPWORDS",
  "DATA",
  "data",
  "LOCOP",
  "LOCNUM",
  "LOCCODE"
#define strcmd_docid            0
#define strcmd_docdel           1
#define strcmd_docptr           2
#define strcmd_stopwords        3
#define strcmd_data             4
#define strcmd_data_tolower     5
#define strcmd_locop            6
#define strcmd_locnum           7
#define strcmd_loccode          8
} ;

/* ------------------------------------------------------------------------ */
static int l2s (long l, char *s)
{
  int ch;
  s[4]= 0;
  ch= l % 64; l /= 64; s[3]= (char) 33+ch;
  ch= l % 64; l /= 64; s[2]= (char) 33+ch;
  ch= l % 64; l /= 64; s[1]= (char) 33+ch;
  ch= l % 64; l /= 64; s[0]= (char) 33+ch;
  return 0;
}

/* (description) ---------------------------------------------------------- */
long lmd_read_stream (struct LMDC_CONTROL *lmdc, char *fn)
{
  FILE *fi;
  int fi_open= 0;
  int j;
  int ll;
  long docid= 1L;
  long docptr= -1L;
  char docid_str [10];
#define MODE_META 0
#define MODE_DATA 1
#define MODE_Data 2
  int mode= MODE_META;
  int cmd;
  int locop= LOC_CODE_SET;
  int locnum= 0;
  long loccode= 0L;
  long word_count= 0L;
  int min_wordlength;
  int max_wordlength;
  char *line;
  int LINE_SIZE;
  int rc;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (line= lmdc->LMDC_buffer1) == (char *) 0
     ) return -1L;

  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;
  LINE_SIZE= lmdc->LMDC_buffer_size;

  if (strcmp (fn, "-") == 0) fi= stdin;
  else
  {
    fi= fopen (fn, "r");
    fi_open= 1;
  }

  if (fi == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1L;
  }

  for (;;)
  {
    j= fread_line (fi, line, LINE_SIZE);
    if (j <= 0 && feof (fi)) break;
    if (*line == 0) continue;

    switch (mode)
    {
      case MODE_META:
        if (line[0] == '#') break;

#ifdef NOT_NOW
        if (line[0] == '-')
        {
          interpret_parameter (line);
          break;
        }
#endif

        cmd= find_command (line, stream_commands, 0, strcmd_loccode);
        switch (cmd)
        {
          case strcmd_docid:
            docid= get_parameter_value (&line[6]);
            /**** long_to_hex (docid, docid_str); ***/
            l2s (docid, docid_str);
/*** printf ("docid=%ld docid_str='%s'\n", docid, docid_str); ***/
            break;
          case strcmd_docdel:
printf (">>> deleting document id: %ld\n", docid);
            lmd_discard_document_id (lmdc, docid);
            break;
          case strcmd_docptr:
            docptr= get_parameter_value (&line[7]);
printf ("docptr=%ld\n", docptr);
            break;
          case strcmd_data:
            mode= MODE_DATA;
            break;
          case strcmd_data_tolower:
            mode= MODE_Data;
            break;
          case strcmd_stopwords:
            mode= MODE_DATA;
            docid= 0L;  /* document id code for stop words */
            break;
          case strcmd_locop:
            locop= (int) get_parameter_value (&line[6]);
/*** printf ("locop=%d\n", locop); ***/
            break;
          case strcmd_locnum:
            locnum= (int) get_parameter_value (&line[7]);
/*** printf ("locnum=%d\n", locnum); ***/
            break;
          case strcmd_loccode:
            loccode= get_parameter_value (&line[8]);
/*** printf ("loccode=%ld\n", loccode); ***/
            break;
          default:
            printf ("unknown stream command: %s\n", line);
            break;
        }
        break;

      case MODE_Data:
        to_lower (line);
      case MODE_DATA:
        if (strcmp (line, ".") == 0)
        {
          mode= MODE_META;
          break;
        }
        ll= strlen (line);
        if (ll < min_wordlength) continue;
        if (ll > max_wordlength) line [max_wordlength]= 0;
        rc= lmd_idx (lmdc, line, docid, docptr, docid_str+4/*** TMP ***/,
                     locop, locnum, loccode);
        if (rc == -1)
        {
          printf ("error in lmd_idx, stopping! docid_str='%s'\n", docid_str);
          goto STOP;
        }
        if (rc == 0) word_count++;
        break;
    }
  }

STOP:
  if (fi_open == 1) fclose (fi);

  return word_count;
}

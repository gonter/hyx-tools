/*
 *  FILE %nl_kr/lutmake.c
 *
 *  generate LUTs from different types of lookup tables and
 *  other files
 *
 *  hot spots in this file:
 *  -  HELP
 *  -  prototypes
 *  -  T2D
 *
 *  written:       1989 03 29
 *                 1990 11 16: Revision
 *                 1991 03 17: Revision; AIX
 *                 1993-02-28: complete redesign of the word reference system
 *                 1993-08-15: cooked stream mode
 *  latest update: 2001-01-28 22:33:46
 *  $Id: lutmake.c,v 1.5 2002/07/04 18:08:49 gonter Exp $
 *
 */

#define REAL_AUTHOR

#include <stdio.h>
#include <stdlib.h>

#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif

#include <ctype.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/hyx.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
#define STDHLP stdout

#define MATCH_C_max 24
static char *match_v [MATCH_C_max];     /* array of match sets              */
static int match_c= 0;                  /* number of sets to match          */

#define FNM_SIZE 1024
static char filenm [FNM_SIZE];

static int verbosity= 0;

/* ------------------------------------------------------------------------ */
static int read_mode= RM_words;

/* statistics: ------------------------------------------------------------ */
static long word_cnt= 0;
static long word_cnt_unique= 0;
static long total_bytes_read= 0;
extern long YTREE_ALLOCATED;
extern long YTREE_ALLOC_SIZE;
static int files_processed= 0;

/* ------------------------------------------------------------------------ */
static long fileid= 1L;
static int pre_read= 0;                 /* 1 -> LUT File vorher einlesen    */
static int tfb_position= 0;
static int tfb_delimiter= ':';

static struct LMDC_CONTROL *lmdc;
static struct WCRD *wcrd;
static struct ARRAY_CONTROL *arguments;

/* filenames: ------------------------------------------------------------- */
#ifndef __CMS__
static char LUT_file [FNM_SIZE]= "xxx.lt";    /* lookup table               */
static char WR_file  [FNM_SIZE]= "xxx.wr";    /* word reference             */
static char DI_file  [FNM_SIZE]= "xxx.di";    /* document information       */
#define DOCDIR_DD "docdir.dd"
#else
static char LUT_file [FNM_SIZE]= "xxx.lt.a";  /* lookup table               */
static char WR_file  [FNM_SIZE]= "xxx.wr.a";  /* word reference             */
static char DI_file  [FNM_SIZE]= "xxx.di.a";  /* document information       */
#define DOCDIR_DD "docdir.dd.a"
#endif

/* ------------------------------------------------------------------------ */
static int alphabet [256];
static char *default_alphabet=
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_$";

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: lutmake [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... parameter file\n",
  "  -b<fnm> ... simple batch file format\n",
  "  -c<fnm> ... cooked data stream file format (see also: -ms)\n",
  "  -l<lut> ... name of the LUT file; .wr and .di file follow\n",
  "  -t[<fnm>] ... docdir table [DEF: docdir.dd]\n",
  "  -d<id> ... discard reference to document ids\n",
  "  -r  ... pre read LUT\n",
  "  -mw ... read words [DEF]\n",
  "  -m2 ... read TOKENS (alpha pre-release version)\n",
  "  -mf ... read frequency table (set):      code count word\n",
  "  -ml ... read long frequency table (add): count word\n",
  "  -mv ... read veronica file\n",
  "  -ms ... cooked stream mode\n",
  "  -mt ... read tfb file\n",
  "  -mc ... read hyx cluster\n",
  "  -min<n> ... minimal word length; [DEF: 3]\n",
  "              shorter words are ignored\n",
  "  -max<n> ... maximal word length; [DEF: 24]\n",
  "              longer words are truncated\n",
  "  -nh<n> ... number of maximum hits to drop a stop word [DEF: 1000]\n",
  "  -nr<n> ... highest rank of stop words [DEF: 1000]\n",
  "  -s<set> ... name of sets to process; [DEF: take everything]\n",
  "  -of<n> ... set TFB field number\n",
  "  -od<c> ... set TFB delimiter to <c>\n",
  "  -i<id> .. file id code:\n",
  "    id < 0 .. stop words\n",
  "    id = 0 .. hit words\n",
  "    id > 0 .. normal document for reference\n",
  "  -v ... increase verbosity\n",
  "  -xs<str> ... set alphabet string to <str> [DEF: a-z,A-Z,0-9,_,$,*]\n",
  "  -xa<str> ... add string <str> to alphabet\n",
  "  -xd<str> ... delete string <str> from alphabet\n",
  "\n",
  "(@)Alutmake.c 3.11 #D$2002-07-04 20:07:34\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl interpret_parameter (char *par);
int cdecl lut_make (char *fn, void *cd);
int cdecl set_alphabet (char *s);
int cdecl set_lut_file (char *fnm);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  long rv;

  if (argc <= 1) goto HLP;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
      || (lmdc= lmd_create_control ()) == (struct LMDC_CONTROL *) 0
     )
  {
    fprintf (stderr, "fatal error: can't create control structure!\n");
    return 1;
  }

  wcrd2_set_processor (wcrd, WCRD_set_file_processor, lut_make,
                       (void *) lmdc);
  set_alphabet (default_alphabet);

  for (i= 1; i < argc; i++)
    switch (interpret_parameter (argv [i]))
    {
      case 0:
        break;

HLP:
#include <gg/help.inc>
    }

  /* Lese Vorbereitung ------- */
  switch (read_mode)
  {
    case RM_hyx_cluster:
    case RM_tokens:
    case RM_stream:
    case RM_tfb:
    case RM_veronica:
      if (pre_read)
      {
        long words_in_wr_table;

        lmd_RL4 (lmdc, LUT_file);
        words_in_wr_table= lmd_read_tables (lmdc, WR_file, DI_file);
      }
      break;
    default:
      if (pre_read) lmd_RL4 (lmdc, LUT_file);
      break;
  }

  lmdc->LMDC_verbosity= verbosity;
  if (array_elements (arguments))
  {
    char *arg;

    while ((arg= (char *) array_shift (arguments)) != (char *) 0)
    {
      if (arg [0] == '-')
      {
        switch (arg [1])
        {
          case 'f': case 'F':
            if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
            {
              fprintf (stderr, "File %s not found!\n", arg+2);
              break;
            }
            for (;;)
            {
              j= fread_line (fi2, filenm, FNM_SIZE);
              if (j <= 0 && feof (fi2)) break;
              if (filenm [0] == '-')
              {
                if (interpret_parameter (filenm) == -1)
                  goto HLP;
              }
              else wcrd2_wildcards (wcrd, filenm);
            }
            fclose (fi2);
            break;
          case 'd': case 'D':
            lmd_discard_document_id (lmdc, get_parameter_value(arg+2));
            break;
          case 'b': case 'B':
            if ((rv= lmd_batch_process (lmdc, arg+2, verbosity)) > 0L)
              word_cnt += rv;
            break;
          case 'i': case 'I':
            fileid= get_parameter_value (arg+2);
            break;
          case 'c': case 'C':
            if ((rv= lmd_read_stream (lmdc, arg+2)) > 0L)
              word_cnt += rv;
            break;
          case 0:
            lut_make ("-", (void *) lmdc);
        }
      }
      else wcrd2_wildcards (wcrd, arg);
    }
  }

  printf ("%d files processed; %ld bytes_read\n",
         files_processed, total_bytes_read);

  switch (read_mode)
  {
    case RM_hyx_cluster:
    case RM_tokens:
    case RM_veronica:
    case RM_stream:
    case RM_tfb:
      printf ("processing word list and writing reference tables\n");
      lmd_write_tables (lmdc, WR_file, DI_file, LMDD_mode_full);
      break;
  }

  word_cnt_unique= (long) lmd_PL (lmdc->LMDC_ytree, LUT_file, (char *) 0);
  printf ("%ld words, %ld unique\n", word_cnt, word_cnt_unique);
  lmd_print_04statistics (lmdc, stdout);

  printf ("%ld YTREE-nodes using %ld byte\n",
          YTREE_ALLOCATED, YTREE_ALLOC_SIZE);

  return 0;
}

/* ------------------------------------------------------------------------ */
int interpret_parameter (char *par)
{
  int j;
  int ch;
  long rv;

  if (par [0] == '-')
    switch (par [1])
    {
      case 'b': case 'B':
      case 'd': case 'D':
      case 'f': case 'F':
      case 'i': case 'I':
      case 'c': case 'C':
        if (par [2] == 0) break;
        array_push (arguments, (void *) par);
        break;

      case 't': case 'T':
        if ((rv= lmd_docdir_process (lmdc,
                                     (par [2] == 0) ? DOCDIR_DD : par+2,
                                     match_c, match_v, verbosity))
            > 0L) word_cnt += rv;
        read_mode= RM_tokens;
        break;

      case 'l': case 'L':
        if (!par [2]) break;
        set_lut_file (par+2);
        break;

      case 'r': case 'R':
      case 'v': case 'V':
        for (j= 1; par [j]; j++)
          switch (par [j])
          {
            case 'r':
              pre_read= 1;
              break;
            case 'v': case 'V':
              verbosity++;
              break;
            case 'R':
              wcrd2_set_subdirs (wcrd, 1);
              break;
            default: return -1;
          }
        break;

      case 'm': case 'M':
        switch (par [2])
        {
          case 'c': case 'C': read_mode= RM_hyx_cluster;break;
          case 'w': case 'W': read_mode= RM_words;      break;
          case 'v': case 'V': read_mode= RM_veronica;   break;
          case 'f': case 'F': read_mode= RM_fcy;        break;
          case 'l': case 'L': read_mode= RM_lfcy;       break;
          case '2':           read_mode= RM_tokens;     break;
          case 's': case 'S': read_mode= RM_stream;     break;
          case 't': case 'T': read_mode= RM_tfb;        break;
            break;

          case 'a': case 'A':
            ch= par [3];
            if (ch == 'x' || ch == 'X')
              lmdc->LMDC_max_wordlength= (int) get_parameter_value (par+4);
            break;
          case 'i': case 'I':
            ch= par [3];
            if (ch == 'n' || ch == 'N')
              lmdc->LMDC_min_wordlength= (int) get_parameter_value (par+4);
            break;
          default: return -1;
        }
        break;

      case 'n': case 'N':
        switch (par [2])
        {
          case 'h': case 'H':
            lmdc->LMDC_max_word_count= get_parameter_value (par+3);
            break;
          case 'r': case 'R':
            lmdc->LMDC_stop_word_limit= get_parameter_value (par+3);
            break;
          default: return -1;
        }
        break;

      case 'o': case 'O':
        switch (par [2])
        {
          case 'd': case 'D':
            tfb_delimiter= par [3];
            break;
          case 'f': case 'F':
            tfb_position= (int) get_parameter_value (par+3);
            break;
          default: return -1;
        }
        break;

      case 's': case 'S':
        if (match_c+1 < MATCH_C_max) match_v [match_c++]= par+2;
        break;

      case 'x': case 'X':
        switch (par [2])
        {
          case 'a': case 'A':
            put_chartable (alphabet, par+3, 1);
            break;
          case 'd': case 'D':
            put_chartable (alphabet, par+3, 0);
            break;
          case 's': case 'S':
            set_alphabet (par+3);
            break;
          default: return -1;
        }
        break;

      case 0: goto IS_PAR; /* - means stdin */
      default: return -1;
    }
  else
  {
IS_PAR:
    array_push (arguments, (void *) par);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int lut_make (char *fn, void *cd)
{
  long rv= 0L;
  struct LMDC_CONTROL *lmdc;

  lmdc= (struct LMDC_CONTROL *) cd;

  switch (read_mode)
  {
    case RM_words:
      rv= lmd_read_words (lmdc, fn);
      break;

    case RM_fcy:
      rv= lmd_read_fcy (lmdc, fn);
      break;

    case RM_lfcy:
      rv= lmd_read_long_fcy (lmdc, fn);
      break;

    case RM_tokens:
      {
        char docid_str [10];

        long_to_hex (fileid, docid_str);
        rv= lmd_read_tokens (lmdc, fn, fileid, docid_str, 0L, 0L,
                             0x7FFFFFFFL, verbosity);
        if (fileid > 0L) fileid++;
      }
      break;

    case RM_veronica:
      rv= lmd_veronica_process (lmdc, fn, alphabet);
      break;

    case RM_stream:
      rv= lmd_read_stream (lmdc, fn);
      break;

    case RM_tfb:
      rv= lmd_read_tfb (lmdc, fn, tfb_position, tfb_delimiter, alphabet);
      break;

    case RM_hyx_cluster:
      {
        char *fn_idx;

        set_lut_file (fn);
        fnmcpy (LUT_file, fn, ".lt");
        if ((fn_idx= fnmcpy2 (fn, ".idx")) != (char *) 0)
        {
          rv= lmd_read_hyx_cluster (lmdc, fn, fn_idx, alphabet);
          free (fn_idx);
        }
      }
      break;

    default:
      return -1;
  }

  if (rv > 0L) word_cnt += rv;
  files_processed++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int set_alphabet (char *s)
{
  int i;

  for (i= 0; i < 256; i++) alphabet [i]= 0;
  return put_chartable (alphabet, s, 1);
}

/* ------------------------------------------------------------------------ */
int set_lut_file (char *fnm)
{
  strcpy (LUT_file, fnm);
  fnmcpy (WR_file, LUT_file, ".wr");
  fnmcpy (DI_file, LUT_file, ".di");

  return 0;
}

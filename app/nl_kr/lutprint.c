/*
 *  FILE %usr/nl_kr/lutprint.c
 *
 *  Sortieren und Ausgeben von LUT-Dumps mit Analyse Info
 *  - HELP
 *  - prototypes
 *
 *  written:       1991 02 16
 *                 1991 03 19: Revision; AIX
 *  latest update: 1995-07-09
 *  $Id: lutprint.c,v 1.2 2001/08/26 23:25:54 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/lookup.h>

#define STDHLP stdout

/* ------------------------------------------------------------------------ */
static int verbose_mode = 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: lutprint [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
#ifdef SUBDIRS
  "  -s -r ... subdirs\n",
#endif
  "  -v ... verbose mode\n",
  "\n",
  "(@)Alutprint.c 2.03 #D$2001-08-25 23:32:13\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl lutprint (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;


  if (argc <= 1) goto HLP;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       lutprint, (void *) 0);

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'f': case 'F':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;

        case 'r': case 'R':
        case 's': case 'S':
        case 'v': case 'V':
          for (j= 1; argv [i][j]; j++)
          switch (argv [i][j])
          {
            case 'r': case 'R':
            case 's': case 'S':
              wcrd2_set_subdirs (wcrd, 1);
              break;
            case 'v': case 'V':
              verbose_mode++;
              break;
            default:
              goto HLP;
          }
          break;

HLP:
#include <gg/help.inc>
      }
      else array_push (arguments, (void *) arg);
  }

  wcrd2_arguments (wcrd, arguments);

STOP:
  print_sorted (stdout);

  return 0;
}

/* ------------------------------------------------------------------------ */
int lutprint (char *fn, void *cd)
{
  FILE *fi;
  long word_count;
#define WORT_SIZE 256
  char wort [WORT_SIZE];
  int wc= 0;
  int rc;
  char *fields [2];
  long total_word_count= 0;

#ifdef MSDOS
  cd;
#endif

  fprintf (stderr, "Processing file %s\n", fn);
  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2;
  }

  for (;;)
  {
    rc= fread_line (fi, wort, WORT_SIZE);
    if (rc <= 0 && feof (fi)) break;

    if (isolate_tokens (wort, fields, 2) != 2) continue;

    word_count= get_parameter_value (fields [0]);
    sort_by_frequency (fields [1], word_count);
    wc++;
    total_word_count += word_count;
    if ((wc % 100) == 0) fprintf (stderr, "Words: %6d\r", wc);
  }

  fprintf (stderr, "Words: %6d\n... done\n", wc);
  fprintf (stdout, "Words: %6d;   total words: %7ld\n",
           wc, total_word_count);

  fclose (fi);

  return 0;
}

/*
 *  FILE %ta/ta.c
 *
 *  Textul Analysis
 *
 *  written:       1990 11 11
 *                 1992 11 15
 *  latest update: 1996-12-22 20:31:22
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/parse.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/ta.h>

#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>

#define STDHLP stderr

/* ------------------------------------------------------------------------ */
static char filenm [256];
static int verbose_mode= 0;
static struct HYX_PARSER_CLASS *hpc= (struct HYX_PARSER_CLASS *) 0;
static struct HYX_PARSER_STATUS *hps= (struct HYX_PARSER_STATUS *) 0;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: ta [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<filename> ... list of files\n",
  "  -R ... recurse through the subdirectories\n",
  "  -v ... verbose mode\n",
  "  -m<n> .. set output mode=n\n",
  "    4 ... place ta.* sgml tags\n",
  "\n",
  "(@)Ata.c 1.04 #D$1996-12-22 20:32:04\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  int tm= 4;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor, main_fnc, (void *) 0);
  if (argc <= 1) goto HLP;

  if ((hpc= hyx_init_parser_class ()) == (struct HYX_PARSER_CLASS *) 0
      || (hps= hyx_parser_reset (hpc)) == (struct HYX_PARSER_STATUS *) 0
     )
  {
    fprintf (stderr, "fatal error: can't create control structure!\n");
    return 1;
  }

  /* ta_transmit_mode (tm= 2); */

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
        case 'm': case 'M':
          /* ta_transmit_mode (tm= (int) get_parameter_value (arg+2)); */
          break;

        case 'r': case 'R':
        case 's': case 'S':
        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'r': case 'R':
              case 's': case 'S':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
            }
          break;

HLP:
#include <gg/help.inc>
         }
    else array_push (arguments, (void *) arg);
  }

  hyx_read_tag_definition (hpc, set_etc_filename ((char *) 0, "lexicon.tags"));

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
  {
    if (arg [0] == '-')
    {
      if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
      {
        fprintf (stderr, "couldn't open file %s!\n", arg+2);
        break;
      }

      for (;;)
      {
        fscanf (fi2, "%s", filenm);
        if (feof (fi2)) break;
        if (wcrd2_wildcards (wcrd, filenm) == -1)
        {
          fclose (fi2);
          goto STOP;
        }
      }
      fclose (fi2);
    }
    else
    {
      if (wcrd2_wildcards (wcrd, arg) == -1) goto STOP;
    }
  }

STOP:

  if (tm == 4)
  {
#ifdef DIAG
    printf ("-------------------- BEGIN DIAGNOSE ------------------------\n");
    diag_display_markup (stdout, hps->HPS_tx_list, 0, 1);
    printf ("--------------------  END  DIAGNOSE ------------------------\n");
#endif /* DIAG */
    hyx_ta_flush_node_list (hps);
    ta012_finish (stdout);
#ifdef REDESIGN
    ta_print_toc (stdout, "$$root");
#endif /* REDESIGN */
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn, void *cd)
{
#ifdef MSDOS
  cd;
#endif

  return (int) hyx_ta_parse_file (hps, fn, (long) 0, 0x7FFFFFFFL);
}

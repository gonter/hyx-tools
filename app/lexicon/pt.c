/*
 *  FILE %lexicon/pt.c
 *
 *  written:       1991 03 12
 *  latest update: 1996-02-18  9:53:23
 *  $Id: pt.c,v 1.5 2004/05/08 15:40:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/array.h>
#include <gg/filename.h>
#include <gg/diagnose.h>
#include <gg/parse.h>
#include <gg/sgml.h>

#ifdef MSDOS
#include <conio.h>
#endif

/* ------------------------------------------------------------------------ */
static char entry_key [ENTRY_KEY_SIZE];

static long end_tags [] = { SGML_TAG_endframe };

static int print_text_list= 0;
static int print_processed_list= 0;
static int print_markup_structure= 1;
static int print_diagnostic_mode= 0;
static int do_restructure= 1;
static int do_strip= 1;
static int do_strip_tags= 1;
static FILE *FO;
static char *fnm_out= (char *) 0;

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "usage: pt [options] {file name}\n",
  "normal options:\n",
  "  -X .. display everything\n",
  "  -H .. process HTML\n",
  "  -o<fnm> ... write output to file\n",
  "  -a<fnm> ... write output to file\n",
  "toggle options: upper case=OFF, lower case=ON\n",
  "  -d .. turn on diagnose [DEF: off]\n",
  "  -m .. markup [DEF: on]\n",
  "  -p .. processed [DEF: off]\n",
  "  -t .. text [DEF: off]\n",
  "  -r .. restructure [DEF: on]\n",
  "  -s .. strip [DEF: on]\n",
  "  -z .. strip tags [DEF: on]\n",
  "\n",
  "(@)Apt.c 1.05 #D$2004-05-08 11:10:20\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv[]);
int cdecl read_file (struct HYX_PARSER_CLASS *hpc, char *fn);
int cdecl display_list (struct HYX_PARSER_CLASS *hpc,
  struct TEXT_ELEMENT *te, int verbosity);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i;
  int j;
  char *tag_definitions;
  struct HYX_PARSER_CLASS *hpc;
  struct ARRAY_CONTROL *arguments;
  char *arg;
  FO= stdout;
  tag_definitions= set_etc_filename ((char *) 0, "lexicon.tags");

  if (argc <= 1
      || (hpc= hyx_init_parser_class ()) == (struct HYX_PARSER_CLASS *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) goto HLP;

#ifdef DIAG
  print_diagnostic_mode= 1;
  print_processed_list= 1;
  print_text_list= 1;
#endif /* DIAG */

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];
    if (arg [0] == '-')
    {
      for (j= 1; arg [j]; j++)
        switch (arg [j])
        {
          case 'X': print_diagnostic_mode= 1;
                    print_markup_structure= 1;
                    print_processed_list= 1;
                    do_restructure= 1;
                    do_strip= 1;
                    do_strip_tags= 1;
                    print_text_list= 1;
                    break;

          case 'd': print_diagnostic_mode= 1; break;
          case 'D': print_diagnostic_mode= 0; break;
          case 'm': print_markup_structure= 1; break;
          case 'M': print_markup_structure= 0; break;
          case 'p': print_processed_list= 1; break;
          case 'P': print_processed_list= 0; break;
          case 'r': do_restructure= 1; break;
          case 'R': do_restructure= 0; break;
          case 's': do_strip= 1; break;
          case 'S': do_strip= 0; break;
          case 'z': do_strip_tags= 1; break;
          case 'Z': do_strip_tags= 0; break;
          case 't': print_text_list= 1; break;
          case 'T': print_text_list= 0; break;

          case 'H':
            hpc->HPC_minimization_char= 0;
            hpc->HPC_meta_flags |= HPC_META_HTML;
            break;

          case 'o': case 'a':
            fnm_out= arg+2;
            FO= fopen (fnm_out, (arg [j] == 'a') ? "a" : "w");
            goto DONE;
            break;

HLP:
#include <gg/help.inc>
      }

DONE: ;
    }
    else
    {
      array_push (arguments, (void *) arg);
    }
  }

  hyx_read_tag_definition (hpc, tag_definitions);

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
  {
    read_file (hpc, arg);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int read_file (struct HYX_PARSER_CLASS *hpc, char *fn)
{
  FILE *fi;
  struct TEXT_ELEMENT *tx_new_entry;
  struct MARKUP *markup_new;
  long chars_read;
  int rc;

  if ((fi= fopen (fn, "r")) == (FILE *) 0) return -1;
  printf ("pt.c: reading file fn='%s'\n", fn);

  for (;;)
  { 
    rc= hyx_parse1_file (hpc, fi, &tx_new_entry, end_tags, 1,
                         0x7FFFFFFFL, &chars_read);

    if (tx_new_entry == (struct TEXT_ELEMENT *) 0) break;

    if (rc != 0 || chars_read == 0L)
    {
      printf ("hyx_parse_file: rc=%d chars_read=%ld diag=0x%08lX\n",
              rc, chars_read, gg_diagnose);
      if (gg_diagnose != LEX_RT_no_frame_close) break;
    }

    if (print_text_list)
    {
      printf ("---------------- text list --------------------\n");
      display_list (hpc, tx_new_entry, 0);
    }

    if (rc != 0 && (gg_diagnose == LEX_RT_no_frame_close)) break;

    if (do_restructure)
    {
      dict_restructure_new_entry (hpc, &tx_new_entry,
                                  entry_key, ENTRY_KEY_SIZE,
                                  do_strip,
                                  (struct TEXT_ELEMENT *) 0,
                                  (struct TEXT_ELEMENT *) 0);

      if (tx_new_entry == (struct TEXT_ELEMENT *) 0)
      {
        printf ("tx_new_entry == NIL\n");
        break;
      }

      printf ("\nentry_key= '%s'\n", entry_key);

      if (*entry_key == 0)
      {
        printf ("ignoring empty entry\n");
        /* continue; */
      }
    }

    if (print_processed_list)
    {
      printf ("------------ processed text list --------------\n");
      display_list (hpc, tx_new_entry, 0);
    }

    if (print_markup_structure)
    {
      printf ("--- creating markup tree\n");
      rc= hyx_text_to_markup (hpc, tx_new_entry, &markup_new);
      tx_new_entry= NULL;
      if (rc == -1) break;
      printf ("--------------- markup tree -------------------\n");
      display_list (hpc, (struct TEXT_ELEMENT *) markup_new, 1);
    }
  }
DONE:
  fclose (fi);

  return 0;
}

/* ------------------------------------------------------------------------ */
int display_list (
struct HYX_PARSER_CLASS *hpc,
struct TEXT_ELEMENT *te,
int verbosity)
{
  if (print_diagnostic_mode)
       diag_display_markup (FO, hpc, te, 0, verbosity, 1, do_strip_tags);
  else display_markup (FO, hpc, te, 0, verbosity, 1, do_strip_tags);

  return 0;
}

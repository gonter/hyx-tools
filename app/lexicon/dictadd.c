/*
 *  FILE %lexicon/dictadd.c
 *
 *  Files dem Dictionary einverleiben
 *  - HELP
 *
 *  written:       1991 03 17
 *  latest update: 2000-08-26 15:19:08
 *
 */
static char ID []= "$Id: dictadd.c,v 1.5 2003/06/25 10:12:06 gonter Exp $\n";

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/hytxt.h>
#include <gg/parse.h>
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/sgml.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#ifdef MSDOS
#include <conio.h>
#endif

#ifndef MSDOS
#define BBC_SERVER
#endif

#ifdef BBC_SERVER
#include <gg/bbch.h>
static int port_number= 0;
static char *key_file= ".kredenz.tfb";
#endif /* BBC_SERVER */

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static int do_strip= 1;
static int write_nl= 1;
static int queue_size= QUEUE_SIZE;
static int do_query= 0;

static char *head_tag= (char *) 0;
static char *tail_tag= (char *) 0;

static char head_tag_str [256];

static char *def_tag_definition= "lexicon.tags";
static char *tag_definition= (char *) 0;
#define FILENAME_SIZE 256
static char lexicon_setup  [FILENAME_SIZE]= "alexicon.stp";
static int setup_readin= 0;

#define MAX_LINE 256
static char line [MAX_LINE];

static struct HYX_CLUSTER_CONTROL *hcc;
static struct LEXICON_CONTROL *lcc;
static struct HYX_PARSER_CLASS *hpc;
static char *FNM_HYX= "alexicon.hyx";

/* ------------------------------------------------------------------------ */
#define NUM_END_TAGS 1
static long end_tags [NUM_END_TAGS]= { (long) SGML_TAG_endframe } ;

/* ------------------------------------------------------------------------ */
static char VERSION []= "(@)Adictadd.c 1.39 #D$2000-08-26 15:19:29\n";

static char *HELP [] =
{
  "USAGE: dictadd [options] {file name}\n",
  "  add files in lexicon format to an existing main lexicon\n",
#ifdef BBC_SERVER
  "  with Black Board Controller\n",
#endif /* BBC_SERVER */
  "OPTIONS:\n",
#ifdef BBC_SERVER
  "  -p<num> ... port number to listen on\n",
#endif /* BBC_SERVER */
  "  -c<fnm> ... cluster name\n",
  "  -l<fnm> ... list of files\n",
  "  -t<fnm> ... tag definition file\n",
  "  -s<fnm> ... lexicon setup file\n",
  "  -i<itemstr>  ... generate item tag <I itemstr>\n",
  "  -m<c> ... processing mode\n",
  "     m ... merge old and new entry [DEF]\n",
  "     r ... replace existing entry by new one\n",
  "     c ... check new entries\n",
  "     l ... lookup\n",
  "     d<num> ... divide mode; 1, 2, or 3 chars\n",
  "  -n<mode> ... mode for generating frame names\n",
  "     m .. md5 hash strings (0)\n",
  "     e .. entry key (1) [DEF]\n",
  "     i .. index (2) [BUG: DOESN'T WORK RIGHT NOW!]\n",
  "  -o<opt> ... processing options\n",
  "    n ... write new lines after text [DEF]\n",
  "    N ... don't write new lines after text\n",
  "    s ... text stripping on [DEF]\n",
  "    S ... text stripping off\n",
  "  -q<num> ... queue size [DEF: 4096 Unix, 128 DOS]\n",
  "  -x ... write XFN instead of full lut (incremental mode)\n",
  "  -v ... verbose mode\n",
  "  -? ... query default values\n",
  "Notes:\n",
  "  <fnm>=- ... stdin or stdout, respectively\n",
  "\n",
  VERSION,
  ID,
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_dict_add (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  int t2d= 0;
  char *arg;
#ifdef BBC_SERVER
  struct BBC_SESSION *bbcs;
#endif /* BBC_SERVER */
  struct LEXICON_GLOBAL_CONTROL *lgc;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if (argc <= 1) goto HLP;

#ifdef MSDOS
  fclose (stdaux);
  fclose (stdprn);
#endif

  if ((hcc= hyx_new_cluster_control ()) == (struct HYX_CLUSTER_CONTROL *) 0
      || (lgc= hyx_new_lexicon_global_control ())
         == (struct LEXICON_GLOBAL_CONTROL *) 0
      || (lcc= hyx_new_lexicon_control ()) == (struct LEXICON_CONTROL *) 0
      || (hpc= hyx_init_parser_class ()) == (struct HYX_PARSER_CLASS *) 0
      || (wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) goto HLP;

  hcc_set_cluster_name (hcc, FNM_HYX);
  hcc->HCC_dict_mode= DAMODE_MERGE;
  hcc->HCC_mode_frame_name= DAFNM_entry_key;
  hcc->HCC_next_index= 1L;

  lcc->LC_lgc= lgc;
  lgc->LGC_EQ_append= &lgc->LGC_EQ_first;

  /* setup end tag codes */
  if ((j= NUM_END_TAGS) > MAX_LC_END_TAGS) j= MAX_LC_END_TAGS;
  for (i= 0; i < j; i++) lcc->LC_end_tags [i]= end_tags [i];
  lcc->LC_end_tag_count= j;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       main_dict_add, (void *) 0);
  tag_definition= set_etc_filename ((char *) 0, def_tag_definition);

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (*arg == '-')
      switch (arg [1])
      {
        case 'c': case 'C':
          hcc_set_cluster_name (hcc, arg +2);
          break;

        case 'i': case 'I':
          if (arg [2])
               sprintf (head_tag_str, "I %s", arg+2);
          else sprintf (head_tag_str, "I");
          head_tag= head_tag_str;
          break;

        case 'l': case 'L':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;

        case 'm': case 'M':
          switch (arg [2])
          {
            case 'c': case 'C':
              hcc->HCC_dict_mode= DAMODE_CHECK;
              break;
            case 'd': case 'D':
              switch ((int) get_parameter_value (arg+3))
              {
                case 1: hcc->HCC_dict_mode= DAMODE_DIVIDE1; break;
                case 2: hcc->HCC_dict_mode= DAMODE_DIVIDE2; break;
                case 3: hcc->HCC_dict_mode= DAMODE_DIVIDE3; break;
                default:
                  goto HLP;
              }
             break;
            case 'm': case 'M':
              hcc->HCC_dict_mode= DAMODE_MERGE;
              break;
            case 'l': case 'L':
              hcc->HCC_dict_mode= DAMODE_LOOKUP;
              break;
            case 'r': case 'R':
              hcc->HCC_dict_mode= DAMODE_REPLACE;
              break;
          }
          break;

        case 'n': case 'N':
          switch (arg [2])
          {
            case 'm': case 'M':
              hcc->HCC_mode_frame_name= DAFNM_md5;
              break;
            case 'e': case 'E':
              hcc->HCC_mode_frame_name= DAFNM_entry_key;
              break;
            case 'i': case 'I':
              hcc->HCC_mode_frame_name= DAFNM_index;
              printf ("BUG: this mode doesn't work currently!\n");
              goto HLP;
              break;
          }
          break;

        case 'o': case 'O':
          switch (arg [2])
          {
            case 'n':
              write_nl= 1;
              break;
            case 'N':
              write_nl= 0;
              break;
            case 's':
              do_strip= 1;
              break;
            case 'S':
              do_strip= 0;
              break;
          }
          break;

#ifdef BBC_SERVER
        case 'p': case 'P':
          if (arg [2] == 0) break;
          port_number= (int) get_parameter_value (arg+2);
          t2d= 1;
          break;
#endif /* BBC_SERVER */

        case 'q': case 'Q':
          if ((queue_size= (int) get_parameter_value (arg+2)) == 0L)
            queue_size= QUEUE_SIZE;
          break;

        case 's': case 'S':
          strcpy (lexicon_setup, arg+2);
          dict_read_setup_file (hcc, lexicon_setup, line, MAX_LINE,
                                &tag_definition);
          setup_readin= 1;
          break;

        case 't': case 'T':
          str_assign (&tag_definition, translate_logic_filename (arg+2));
          break;

        case 'v': case 'V':
        case 'x': case 'X':
        case '?':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'x': case 'X':
                hcc->HCC_lut_mode= HCC_lm_incremental;
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
              case '?':
                do_query= 1;
                break;
            }
          break;

        case 0:
          goto ADD_TO_LIST;

HLP:
#include <gg/help.inc>
      }
      else
      {
ADD_TO_LIST:
        array_push (arguments, (void *) arg);
        t2d= 1;
      }
  }

  if (!setup_readin)
    dict_read_setup_file (hcc, lexicon_setup, line, MAX_LINE,
                          &tag_definition);

  lgc->LGC_queue_size= queue_size;
  lcc->LC_do_strip= do_strip;
  lcc->LC_write_nl= write_nl;
  lcc->LC_head_tag_str= head_tag;
  lcc->LC_tail_tag_str= tail_tag;

  if (do_query)
  {
    printf (VERSION);
    printf ("dictadd default values:\n");
    printf ("lexicon setup file:  %s\n", lexicon_setup);
    printf ("tag definition file: %s\n", tag_definition);
    printf ("lexicon file:        %s\n", hcc->HCC_fnm_hyx);
    printf ("index file:          %s\n", hcc->HCC_fnm_idx);
    printf ("main lut file:       %s\n", hcc->HCC_fnm_lut);

    printf ("queue size: %d [DEF: %d]\n",
            queue_size, QUEUE_SIZE);
    printf (
"procssing options: %s strip white space off text; %s write LF after text\n",
            (do_strip) ? "do" : "don't",
            (write_nl) ? "do" : "don't");
  }

  if (t2d)
  {
    /* 1. bisherige Files einlesen */
    hyx_read_tag_definition (hpc, tag_definition);
    if (dict_check_integrity (hpc) != 0)
    {
      fprintf (stdout,
               "error: tags not defined properly in %s; stopping\n",
               tag_definition);
      return 0;
    }

    dict_add_init (hcc);

    /* 2. neue Files verarbeiten */
    wcrd2_arguments (wcrd, arguments);

#ifdef BBC_SERVER
    if (port_number > 0)
    {
      struct LEX_SESSION *lexs;

      if ((bbcs= bbc_new_session ()) == (struct BBC_SESSION *) 0)
      {
        fprintf (stderr, "could not establish BBC session\n");
        return -1;
      }

      bbcs->BBCS_input1= bbc_authentication_protocol;
      bbcs->BBCS_input2= bbc_lexicon_processor;
      bbcs->BBCS_op= bbc_transmit_text;
      bbcs->BBCS_key_file= key_file;

fprintf (stderr, "input2=0x%08lX\n", bbc_lexicon_processor);
      if ((lexs= (struct LEX_SESSION *)
                 calloc (sizeof (struct LEX_SESSION), 1))
          == (struct LEX_SESSION *) 0)
      {
        fprintf (stderr, "could not initialize\n");
        return -1;
      }
      
      lexs->LEXS_hcc= hcc;
      lexs->LEXS_hpc= hpc;
      lexs->LEXS_lcc= lcc;
      bbcs->BBCS_client_data1= (void *) lexs;

      bbc_main (bbcs, (char *) 0, port_number, 1, (char *) 0, (char *) 0);
    }
#endif /* BBC_SERVER */

    /* 3. veraenderte Files abschliessen */
    hyx_write_stamp (stdout, "p=\"dictadd finish\"");
    fputc ('\n', stdout);
    dict_add_finish (hcc, lcc);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int main_dict_add (char *fn, void *cd)
{
#ifdef MSDOS
  cd;
#endif

  return dict_add_file (hpc, hcc, lcc, fn, verbose_mode);
}

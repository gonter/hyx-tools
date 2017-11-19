/*
 *  FILE %ned/sgmlflt.c
 *
 *  template, standard command interpreter style
 *  - HELP
 *  - prototypes
 *
 *  written:       1997-08-03
 *  latest update: 1997-08-04 12:47:51
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include "ed.h"
#include "proto.h"

#define STDHLP stdout

static char *NED_VERSION= "sgmlflt 0.00";       /* included by sbr */

/* ------------------------------------------------------------------------ */
struct X_CONV
{
  int replace;
  int verbose;

  char *buffer;
  int buffer_size;
} ;

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: sgmlflt [options] {file name}\n",
  "OPTIONS:\n",
  "  -t2s ... text to sgml\n",
  "  -s2t ... sgml to text\n",
  "  -batch ... arguments are names of batch files\n",
  "  -o ... overwrite original file\n",
  "  -f<fnm> ... list of files\n",
  "  -r ... subdirs\n",
  "  -v ... verbose mode\n",
  "EXAMPLES:\n",
  "\n",
  "Batchfile format\n",
  "  text_to_sgml fnm-text fnm-sgml [fnm-ftr]\n",
  "  sgml_to_text fnm-sgml fnm-text [fnm-ftr]\n",
  "NOTE: The name of the feature file is optional and will be\n",
  "      derived from the name of the text file if left unspecified.\n",
  "\n",
  "(@)Asgmlflt.c 0.00 #D$1997-08-03 16:47:30\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl ned_tool_text_to_sgml (char *fnm, void *cd);
int cdecl ned_tool_sgml_to_text (char *fnm, void *cd);
int cdecl ned_tool_batch_sgml_conv (char *fnm, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;
#define OP_undef        0
#define OP_text_to_sgml 1
#define OP_sgml_to_text 2
#define OP_batch        3
  int op_mode= OP_undef;
  struct X_CONV *x_conv;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
      || (x_conv= (struct X_CONV *) calloc (sizeof (struct X_CONV), 1))
                  == (struct X_CONV *) 0
     ) return 1;

  if (argc <= 1) goto HLP;

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

        case 't':
          if (strcmp (arg, "-t2s") == 0) op_mode= OP_text_to_sgml;
          break;

        case 's':
          if (strcmp (arg, "-s2t") == 0) op_mode= OP_sgml_to_text;
          break;

        case 'b':
          if (strcmp (arg, "-batch") == 0) op_mode= OP_batch;
          break;

        case 'o': case 'O':
        case 'r': case 'R':
        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                x_conv->verbose++;
                break;
              case 'o': case 'O':
                x_conv->replace= 1;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg[j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  switch (op_mode)
  {
    case OP_text_to_sgml:
      wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                           ned_tool_text_to_sgml, (void *) x_conv);
      break;

    case OP_sgml_to_text:
      wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                           ned_tool_sgml_to_text, (void *) x_conv);
      break;

    case OP_batch:
      wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                           ned_tool_batch_sgml_conv, (void *) x_conv);
      break;

    default:
      fprintf (stderr, "undefined operation mode!\n");
      goto HLP;
  }

  wcrd2_arguments (wcrd, arguments);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tool_text_to_sgml (char *fnm, void *cd)
{
  char *ftr_name;
  char *sgml_name= (char *) 0;
  char *out_name;
  struct X_CONV *x_conv;

  if ((x_conv= (struct X_CONV *) cd) == (struct X_CONV *) 0) return -1;

  ftr_name= fnmcpy2 (fnm, ".ftr");

  if (x_conv->replace)
    out_name= fnm;
  else
    out_name= sgml_name= fnmcpy2 (fnm, ".sgml");

  ned_text_to_sgml (fnm, ftr_name, out_name, 0);

  free_or_what (ftr_name);
  free_or_what (sgml_name);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tool_sgml_to_text (char *fnm, void *cd)
{
  char *ftr_name;
  char *txt_name= (char *) 0;
  char *out_name;
  struct X_CONV *x_conv;

  if ((x_conv= (struct X_CONV *) cd) == (struct X_CONV *) 0) return -1;

  ftr_name= fnmcpy2 (fnm, ".ftr");

  if (x_conv->replace)
    out_name= fnm;
  else
    out_name= txt_name= fnmcpy2 (fnm, ".txt");

  ned_sgml_to_text (out_name, ftr_name, fnm);

  free_or_what (ftr_name);
  free_or_what (txt_name);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tool_batch_sgml_conv (char *fnm, void *cd)
{
#define X_B_SIZE 1024
  struct X_CONV *x_conv;
  int b_size;
  char *buffer;
  int rc;
#define MAX_FIELDS 10
  char *fields [MAX_FIELDS];
  int num_fields;
  char *sub_command;
  FILE *fi;

  if ((x_conv= (struct X_CONV *) cd) == (struct X_CONV *) 0) return -1;

  if ((buffer= x_conv->buffer) == (char *) 0)
  {
    if ((x_conv->buffer= buffer= malloc (X_B_SIZE)) == (char *) 0) return -1;
    x_conv->buffer_size= b_size= X_B_SIZE;
  }
  else
  {
    b_size= x_conv->buffer_size;
  }

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0) return -1;

  for (;;)
  {
    rc= fread_line (fi, buffer, b_size);
    if (rc <= 0 && feof (fi)) break;

    if (buffer [0] == '#') continue;
    num_fields= isolate_tokens (buffer, fields, MAX_FIELDS);
    if (num_fields <= 0) continue;

    sub_command= fields [0];
    if (sub_command [0] == '#') continue;

    if ((strcmp (sub_command, "t2s") == 0
         || strcmp (sub_command, "text_to_sgml") == 0
         || strcmp (sub_command, "text2sgml") == 0
        )
        && num_fields >= 3
       )
    { /* Format: text_to_sgml fnm-text fnm-sgml [fnm-ftr] */
      char *ftr_name;

      ftr_name= (num_fields > 3)
                ? strdup  (fields [3])
                : fnmcpy2 (fields [1], ".ftr");

      ned_text_to_sgml (fields [1], ftr_name, fields [2], 0);
      free_or_what (ftr_name);
    }
    else
    if ((strcmp (sub_command, "s2t") == 0
         || strcmp (sub_command, "sgml_to_text") == 0
         || strcmp (sub_command, "sgml2text") == 0
        )
        && num_fields >= 3
       )
    { /* Format: sgml_to_text fnm-sgml fnm-text [fnm-ftr] */
      char *ftr_name;

      ftr_name= (num_fields > 3)
                ? strdup  (fields [3])
                : fnmcpy2 (fields [1], ".ftr");

      ned_sgml_to_text (fields [2], fields [1], fnm);
      free_or_what (ftr_name);
    }
    else
    {
      printf ("unknown batch command '%s'\n", sub_command);
    }
  }

  fclose (fi);

  return 0;
}

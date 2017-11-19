/*
 *  FILE %sgml/chksgml.c
 *
 *  Check SGML files
 *  - HELP
 *
 *  written:       1991 07 14
 *  latest update: 1996-10-13 21:06:38
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
#define REAL_AUTHOR
#define STDHLP stdout
#define FILENM_SIZE 1024
static char filenm [FILENM_SIZE];

/* ------------------------------------------------------------------------ */
static int verbose_level= 0;
static FILE *outfile= (FILE *) 0;
static int outfile_is_stdout= 0;
static int files_checked= 0;
static int files_errors= 0;
static int flags= 0x000;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: chksgml [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
  "  -r ... subdirs\n",
  "  -t ... print totals\n",
  "  -i ... ignore case\n",
  "  -v[<n>] ... verbose level [DEF: 0]\n",
  "    0 ... print summary only\n",
  "    1 ... print statistics\n",
  "    2 ... print warnings\n",
  "  -o<fnm> ... write stripped output to file (append)\n",
  "  -O<fnm> ... write stripped output to file (overwrite)\n",
  "    fnm=- ... stdout\n",
  "\n",
  "(@)Achksgml.c 2.08 #D$1996-10-13 11:24:34\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl chksgml_main_fnc (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  char *afn;
  char *arg;
  char ch2;
  int print_totals= 0;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if (argc <= 1) goto HLP;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       chksgml_main_fnc, (void *) 0);

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

        case 'o': case 'O':
         if (outfile != (FILE *) 0 && !outfile_is_stdout) fclose (outfile);
         if (arg [2] == 0) break;
         if (strcmp (arg+2, "-") == 0)
         {
           outfile= stdout;
           outfile_is_stdout= 1;
         }
         else
         {
           if ((afn= translate_logic_filename (arg+2)) == (char *) 0)
             afn= arg+2;
           outfile= fopen (afn, (arg [1] == 'O') ? "wb" : "ab");
         }
         break;

        case 'v': case 'V':
          ch2= arg [2];
          if ((ch2 >= '0' && ch2 <= '9') || ch2 == '-')
            verbose_level= (int) get_parameter_value (arg+2);
          else goto VERBINC;
printf (">>> verbose_level= %d\n", verbose_level);
          break;

        case 'i': case 'I':
        case 'r': case 'R':
        case 't': case 'T':
VERBINC:
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'i': case 'I':
                flags |= CHKSGML_Fign_case;
                break;
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 't': case 'T':
                print_totals= 1;
                break;
              case 'v': case 'V':
                verbose_level++;
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

  if (array_elements (arguments))
  {
    int rc;

    while ((arg= (char *) array_shift (arguments)) != (char *) 0)
      if (arg [0] == '-')
      {
        if ((afn= translate_logic_filename (arg+2)) == (void *) 0)
           afn= arg+2;
        if ((fi2= fopen (afn, "rt")) == (FILE *) 0) continue;
        for (;;)
        {
          rc= fread_line (fi2, filenm, FILENM_SIZE);
          if (rc <= 0 && feof (fi2)) break;
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

  if (outfile != (FILE *) 0 && !outfile_is_stdout) fclose (outfile);

  if (print_totals) chksgml_print_total_counter (stdout);

  return (files_errors > 0) ? 1 : 0;
}

/* ------------------------------------------------------------------------ */
int chksgml_main_fnc (char *fn, void *cd)
{
  int rv;

#ifdef MSDOS
  cd;
#endif

  files_checked++;
  if ((rv= chksgml_file (outfile, stdout, fn, verbose_level, 0L, 0x7FFFFFFFL,
                         flags)) != 0) files_errors++;

  return rv;
}

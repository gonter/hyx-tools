/*
 *  FILE %ds/tfb/tfblut.c
 *
 *  Generate and manipulate TFB index files
 *  - HELP
 *  - prototypes
 *
 *  written:       1993-10-19
 *  latest update: 2003-06-15 21:59:49
 *  $Id: tfblut.c,v 1.6 2005/03/11 23:58:28 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/dpp.h>
#include <gg/tfb.h>
#include <gg/sbr.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/filename.h>

#define STDHLP stderr

#ifdef MSDOS
/* #include <io.h> */
#include <conio.h>
#endif

/* ------------------------------------------------------------------------ */
#define MAX_FILENM 256
static char filenm_lut [MAX_FILENM];
static int verbosity= 0;
static int ambigous_key= AK_complain;
static int field_number=        0;
static int field_delimiter=   ':';
static int open_quote=       '\"';
static int close_quote=      '\"';
static int escape_char=      '\\';
static int modification= MK_none;
static int truncation= -1;              /* no truncation */
static int use_pos= -1;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: tfblut [options] {file name}\n",
  "OPTIONS:\n",
  "  -d<c> ... use <c> as field delimiter [DEF: ':']\n",
  "  -dTAB ... isolate fields by TABs\n",
  "  -d    ... isolate fields by white space\n",
  "  -f<fnm> ... list of files\n",
  "  -n<n> ... field number to use [DEF: 0]\n",
  "  -u<n> ... field number to be used as value [DEF: -1]\n",
  "  -p<x> ... key is record position (offset in byte)\n",
  "  -l<x> ... key is record line number\n",
  "            <x>= d..decimal, no leading 0 (%%ld)\n",
  "                 D..decimal, 8 chars fixed with leading 0 (%%08ld)\n",
  "                 x..HEX (%%lX)\n",
  "                 X..HEX with leading 0 (%%08lX)\n",
  "  -t<n> ... truncate indexed field after <n> characters\n",
  "  -mn ... modify key: none [DEF]\n",
  "  -mu ... modify key: to upper\n",
  "  -ml ... modify key: to lower\n",
  "  -a<mode>+ ... ambigous keys\n",
  "                c ... complain [DEF]\n",
  "                n ... don't complain\n",
  "                f ... use first [DEF]\n",
  "                l ... use last\n",
  "  -r ... subdirs\n",
  "  -v ... increase verbosity\n",
  "\n",
  "(@)Atfblut.c 1.14 #D$2005-03-12  0:57:13\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *arg, *arg2;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor, main_fnc, (void *) 0);
  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
    {
      arg2= arg + 2;

      switch (arg [1])
      {
        case 'd':
          if (strcmp (arg2, "TAB") == 0)
          {
            field_delimiter= (int) '\t';
          }
          else
          {
            field_delimiter= (int) ((*arg2) ? *arg2 : -1);
          }
          break;

        case 'f': case 'F':
          if (!*arg2) break;
          array_push (arguments, (void *) arg);
          break;

        case 'n': case 'N':
          field_number= (int) get_parameter_value (arg2);
          break;

        case 'u': case 'U':
          use_pos= (int) get_parameter_value (arg2);
/** printf ("use_pos=%ld\n", use_pos); **/
          break;

        case 't': case 'T':
          if (strcmp (arg, "-TAB") == 0)
          {
            field_delimiter= (int) '\t';
          }
          else
          {
            truncation= (int) get_parameter_value (arg2);
          }
          break;

        case 'a': case 'A':
          for (j= 2; arg [j]; j++)
            switch (arg [j])
            {
              case 'c': case 'C': ambigous_key |= AK_complain;  break;
              case 'n': case 'N': ambigous_key &= ~AK_complain; break;
              case 'f': case 'F': ambigous_key &= ~AK_last;     break;
              case 'l': case 'L': ambigous_key |= AK_last;      break;
            }
          break;

        case 'm': case 'M':
          switch (*arg2)
          {
            case 'n': case 'N': modification= MK_none;     break;
            case 'l': case 'L': modification= MK_tolower;  break;
            case 'u': case 'U': modification= MK_toupper;  break;
          }
          break;

        case 'l': case 'L':
          switch (*arg2)
          {
            case 'd': field_number= -1; break;
            case 'D': field_number= -2; break;
            case 'x': field_number= -3; break;
            case 'X': field_number= -4; break;
          }
          break;

        case 'p': case 'P':
          switch (*arg2)
          {
            case 'd': field_number= -5; break;
            case 'D': field_number= -6; break;
            case 'x': field_number= -7; break;
            case 'X': field_number= -8; break;
          }
          break;

        case 'r': case 'R':
        case 'v': case 'V':
          for (j= 1; argv [i][j]; j++)
            switch (argv [i][j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbosity++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg[j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    }
    else array_push (arguments, (void *) arg);
  }

  wcrd2_arguments (wcrd, arguments);

  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn, void *cd)
{
#ifdef MSDOS
  cd;
#endif

  fnmcpy (filenm_lut, fn, ".lut");

  return
    tfb_make_lut_file (fn, filenm_lut, field_number, field_delimiter,
                       open_quote, close_quote, escape_char, ambigous_key,
                       modification, truncation, verbosity, use_pos);
}

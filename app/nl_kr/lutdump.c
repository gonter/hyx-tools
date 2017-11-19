/*
 *  FILE %nl_kr/lutdump.c
 *
 *  dump LUTs
 *
 *  written:       1989 06 30
 *                 1990 11 16: revision
 *  latest update: 1998-02-28  9:33:57
 *
 */
static char ID[]= "$Id: lutdump.c,v 1.2 2003/06/25 14:38:29 gonter Exp $";

#include <stdio.h>
#include <stdlib.h>
#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/lookup.h>

#define  STDHLP stdout
static int out_mode= 0;
static long dump_start= 0L;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: lutdump [options] {file name}\n",
  "OPTIONS:\n",
  "  -r       ... search recursively through the filesystem\n",
  "  -f<fnm>  ... list of files\n",
  "  -s<pos>  ... start of the dump in the file [DEF: 0x00000000]\n",
  "  -m<mode> ... format of the info value\n", 
  "           ... 0: 0x%%08lX [DEF]\n",
  "           ... 1: %%5u %%5u\n",
  "           ... 2: nothing (just print the key string)\n",
  "\n",
  "(@)A lutdump.c 2.04 #D$2003-06-25 14:43:33\n",
  ID,
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl lut_dump_main_fnc (char *wrd, void *client_data);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if (argc <= 1) goto HLP;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       lut_dump_main_fnc, (void *) 0);

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
          out_mode= (int) get_parameter_value (arg+2);
          break;

        case 's': case 'S':
          dump_start= get_parameter_value (arg+2);
          break;

        case 'r': case 'R':
          wcrd2_set_subdirs (wcrd, 1);
          break;

HLP:
#include <gg/help.inc>
      }
      else array_push (arguments, (void *) arg);
  }

  wcrd2_arguments (wcrd, arguments);

  return 0;
}

/* ------------------------------------------------------------------------ */
int lut_dump_main_fnc (char *fn, void *cd)
{
#ifdef MSDOS
  cd;
#endif

  return lut_dump_file (fn, out_mode, dump_start);
}

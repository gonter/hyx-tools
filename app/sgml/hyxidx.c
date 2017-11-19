/*
 *  FILE %sgml/hyxidx.c
 *
 *  indexing of NED's .HYX HyperText files
 *  -  prototypes
 *  -  HELP
 *
 *  written:       1991 05 17
 *                 1992 12 07: revision
 *  latest update: 1997-01-05 18:20:34
 *  $Id: hyxidx.c,v 1.2 2002/07/17 07:19:40 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>

#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif

/* ------------------------------------------------------------------------ */
#define REAL_AUTHOR
#define STDHLP stderr
#define FILENM_SIZE 1024

static char filenm [FILENM_SIZE];
static int verbose_level= 0;
static char *index_frame= (char *) 0;
static char *md5_frame= (char *) 0;
static int index_flags= HYXIDX_FLAG_default;
static int index_format= HYXIDX_FMT_NORMAL;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: hyxidx [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<filename> ... list of files\n",
  "  -i[<index_frame>] ... generate index frame; [DEF: $$index]\n",
  "  -m[<md5_frame>] ... generate md5 frame; [DEF: $$md5]\n",
  "  -t<n> ... format of index frame\n",
  "    0 ... normal format:\n",
  "          MD5 Checksum, length, link, name\n",
  "    1 ... link format (?)\n",
  "    2 ... docdir format (not available yet)\n",
  "  -x ... force scan through cluster\n",
  "  -r ... subdirs\n",
  "  -v ... verbose mode\n",
  "EXAMPLES:\n",
  "  hyxidx -i %%crf       create a new index for the cross ref cluster\n",
  "NOTES:\n",
  "  option -i causes a full scan through the cluster and the generation\n",
  "  of MD5 checksums over each frame.  This can be used to identify\n",
  "  changed frames later on.\n",
  "  \"RSA Data Security, Inc. MD5 Message-Digest Algorithm\"\n",
  "  This algorithm was specified in rfc1321.\n",
  "\n",
  "(@)Ahyxidx.c 1.29 #D$1997-01-05 18:20:43\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl hyxidx_main_fnc (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
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
                       hyxidx_main_fnc, (void *) 0);

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

        case 'i': case 'I':
          index_frame= (arg [2] == 0) ? "$$index" : arg+2;
          index_flags |= HYXIDX_FLAG_full_scan;
          break;
        case 'm': case 'M':
          md5_frame= (arg [2] == 0) ? "$$md5" : arg+2;
          index_flags |= HYXIDX_FLAG_full_scan;
          break;
        case 't': case 'T':
          /* this parameter should be symbolic! */
          index_format= (int) get_parameter_value (arg+2);
          break;

        case 'v': case 'V':
          if (arg [2] >= '0' && arg [2] <= '9')
            verbose_level= (int) get_parameter_value (arg+2);
          else goto VERBINC;
          break;

        case 'r': case 'R':
        case 'x': case 'X':
VERBINC:
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_level++;
                break;
              case 'x': case 'X':
                index_flags |= HYXIDX_FLAG_full_scan;
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

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
    if (arg [0] == '-')
    {
      if ((fi2= fopen (translate_logic_filename (arg+2), "rt"))
          == (FILE *) 0)
      {
        fprintf (stderr, "File %s not found!\n", arg+2);
        break;
      }

      for (;;)
      {
        j= fread_line (fi2, filenm, FILENM_SIZE);
        if (j <= 0 && feof (fi2)) break;

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

STOP:
  return 0;
}

/* ------------------------------------------------------------------------ */
int hyxidx_main_fnc (char *fn, void *cd)
{
#ifdef MSDOS
  cd;
#endif

  return hyx_index (fn, index_frame, md5_frame, index_format,
                    index_flags, verbose_level);
}

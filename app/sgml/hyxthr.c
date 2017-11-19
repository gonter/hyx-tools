/*
 *  FILE %sgml/hyxthr.c
 *
 *  linearize hypertext frames
 *  see t2d for information about future enhancements
 *
 *  written:       1995-05-21
 *  latest update: 1995-11-19
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif
#include <gg/hytxt.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/parse.h>
#include <gg/filename.h>

#define REAL_AUTHOR
#define STDHLP stderr
#ifdef MSDOS
#define ARG_C_max       24
#else
#define ARG_C_max      240
#endif
static char *arg_v [ARG_C_max];
static int arg_c= 0;

/* quick hack: ------------------------------------------------------------ */
#ifdef MSDOS
#define SUBDIRS                         /* Rekusive Suche durch das         */
                                        /* Filesystem moeglich              */
#define BETTER_FILENAME_MATCH           /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
static int verbose_level= 0;
static int extract_flags= 0;
static char fnm_out [66]= "@hyxseq.@@@";      /* logic fnm translation!!! */
static FILE *fo= (FILE *) 0;
static char *fo_mode= "wb";
static char *thread_name= "inetk";

static struct FILE_SEGMENT *fs_list= (struct FILE_SEGMENT *) 0;
static struct FILE_SEGMENT **fs_append= &fs_list;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: hyxthr [options] {cluster name}\n",
  "  hypertext threader\n",
  "OPTIONS:\n",
  "  -c<cluster> ... name of HYX cluster to extract from\n",
  "  -l<filename>  ... list of frames in a file\n",
  "  -f<framename> ... list of frames in a frame [DEF: $$sequence]\n",
  "  -x<framename> ... extract specified frame\n",
  "  -m<framename> ... extract specified frame after applying md5 hashing\n",
  "  -t ... total recall: extract all frames\n",
  "  -n ... write frame numbers before each frame\n",
  "  -e ... write eoln character after each frame\n",
  "  -o<fnm> ... append output to file\n",
  "  -O<fnm> ... overwrite output to file\n",
  "  -o- ... write to stdout\n",
  "  -q<name> ... thread name\n",
  "  -u ... write frame names to stdout\n",
#ifdef SUBDIRS
  "  -s -r ... subdirs\n",
#endif
  "  -v ... verbose mode\n",
  "\n",
  "(@)Ahyxthr.c 1.04 #D$1995-11-19 12:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  int i, j;
  char *afn;
  struct FILE_SEGMENT *fs;
  long index_number= 0L;
  char *tag_definitions;

  tag_definitions= set_etc_filename ((char *) 0, "lexicon.tags");

  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'f': case 'F':
        case 'l': case 'L':
        case 't': case 'T':
        case 'x': case 'X':
        case 'm': case 'M':
          if ((fs= hyx_make_segment (fs_append, (char *) 0, &argv[i][2],
                                     &index_number,
                                     (int) argv[i][1] & 0x00FF, 0L, 0L))
              != (struct FILE_SEGMENT *) 0)
          {
            fs_append= &fs->FS_next;
          }
          else
          {
            fprintf (stderr, "error: to many items specified\n");
            break;
          }
          break;

        case 'c': case 'C':
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= &argv [i][2];
          break;

        case 'n': case 'N':
          extract_flags |= HYXEF_write_frame_number;
          break;

        case 'e': case 'E':
          extract_flags |= HYXEF_append_eoln;
          break;

        case 'q': case 'Q':
          thread_name= &argv [i][2];
          break;

        case 'u': case 'U':
          extract_flags |= HYXEF_write_frame_name;
          break;

        case 'o': case 'O':
          strcpy (fnm_out, &argv[i][2]);
          fo_mode= (argv[i][1] == 'O') ? "wb" : "ab";
          break;

        case 'v': case 'V':
          if (argv[i][2] >= '0' && argv[i][2] <= '9')
            verbose_level= (int) get_parameter_value (&argv[i][2]);
          else goto VERBINC;
          break;

#ifdef SUBDIRS
        case 'r': case 'R':
        case 's': case 'S':
#endif
VERBINC:
          for (j= 1; argv [i][j]; j++)
            switch (argv [i][j])
            {
#ifdef SUBDIRS
              case 'r': case 'R':
              case 's': case 'S':
                wcrd_set_subdirs (1);
                break;
#endif
              case 'v': case 'V':
                verbose_level++;
                break;
            }
          break;

HLP:
#include <gg/help.inc>
      }
      else if (arg_c+1 < ARG_C_max)
              arg_v [arg_c++] = argv [i];

  if (fs_list == (struct FILE_SEGMENT *) 0)
  {
    if ((fs= hyx_make_segment (fs_append, (char *) 0, "$$sequence",
                               &index_number, FSop_frame, 0L, 0L))
        != (struct FILE_SEGMENT *) 0)
      fs_append= &fs->FS_next;
  }

  read_tag_definition (tag_definitions);

  if (arg_c)
  {
    if (strcmp (fnm_out, "-") == 0)
      fo= stdout;
    else
    if (*fnm_out)
    {
      if ((afn= translate_logic_filename (fnm_out)) == (char *) 0)
        afn= fnm_out;
      fo= fopen (afn, fo_mode);
    }

    for (i= 0; i < arg_c; i++)
    {
#ifdef SUBDIRS
      if (wcrd_wildcards_or_rec (arg_v [i]) == -1) goto STOP;
#else
      wcrd_wildcards (arg_v [i]);
#endif
    }
  }

#ifdef SUBDIRS
STOP:
#endif

  if (fo != (FILE *) 0) fclose (fo);
  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fnm_hyx)
{
  return hyx_thr (fo, fnm_hyx, fs_list, verbose_level, extract_flags,
                  thread_name);
}

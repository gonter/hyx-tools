/*
 *  FILE %sgml/hyxadd.c
 *
 *  add files as frames to a HYX cluster
 *  -  prototypes
 *  -  HELP
 *
 *  written:       1994-06-04
 *  latest update: 1996-12-12 13:03:00
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/hytxt.h>

#define STDHLP stderr

/* ------------------------------------------------------------------------ */
#define FILENM_SIZE 1024
static char filenm [FILENM_SIZE];
static int verbose_mode= 0;
static long index_number= 0L;

static struct FILE_SEGMENT *segments= (struct FILE_SEGMENT *) 0;
static struct FILE_SEGMENT **app_segments= &segments;

static char *fn_hyx= "_dummy_.hyx";
static int t2d= 0;

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP [] =
{
  "USAGE: hyxadd [options] {file name}\n",
  "OPTIONS:\n",
  "  -c<fnm> ... name of the cluster\n",
  "  -f<fnm> ... list of files\n",
  "  -i<num> ... index number [DEF: 0, undefined]\n",
  "  -d<frame> ... mark frame as deleted (place empty data)\n",
  "  -p<frame> ... add named frame by reading contents from pipe (stdin)\n",
  "  -e<beg>;<end>;<file>;<frame> ... explicit specification of segment\n",
  "  -r ... subdirs\n",
  "  -v ... verbose mode\n",
  "\n",
  "(@)A hyxadd.c 1.17 #D$1996-12-12 13:02:57\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl hyx_add_main (char *fn, void *cd);
int cdecl explicit_segment_specification (char *ex);
int cdecl stdin_segment_specification (char *frame_name);
int cdecl deletion_segment (char *frnm);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  char *arg;
  int rc;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       hyx_add_main, (void *) 0);

  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'c': case 'C':
          fn_hyx= arg+2;
          break;

        case 'd': case 'D':
          deletion_segment (arg+2);
          break;

        case 'e': case 'E':
          explicit_segment_specification (arg+2);
          break;

        case 'p': case 'P':
          stdin_segment_specification (arg+2);
          break;

        case 'f': case 'F':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;

        case 'i': case 'I':
          index_number= get_parameter_value (arg+2);
          break;

        case 'r': case 'R':
        case 'v': case 'V':
          for (j=1; arg [j]; j++)
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg [j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
  {
    if (arg [0] == '-')
    {
      if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
      {
        fprintf (stderr, "File %s not opened!\n", arg+2);
        break;
      }

      for (;;)
      {
        rc= fread_line (fi2, filenm, FILENM_SIZE);
        if (rc <= 0 && feof (fi2)) break;

        if (filenm [0] == '-')
        {
          switch (filenm [1])
          {
            case 'e': case 'E':
              explicit_segment_specification (&filenm [2]);
              break;
            case 'd': case 'D':
              deletion_segment (&filenm [2]);
              break;
          }
        }
        else
        {
          if (wcrd2_wildcards (wcrd, filenm) == -1)
          {
            fclose (fi2);
            goto STOP;
          }
        }
      }
      fclose (fi2);
    }
    else
    {
      if (wcrd2_wildcards (wcrd, arg) == -1) goto STOP;
    }
  }

  hyx_print_segment (stdout, segments);
  if (t2d) hyx_add (fn_hyx, segments, verbose_mode);

STOP:

  return 0;
}

/* ------------------------------------------------------------------------ */
int hyx_add_main (char *fn_in, void *cd)
{
  struct FILE_SEGMENT *fs;

#ifdef MSDOS
  cd;
#endif

  if (fn_in == (char *) 0) return -1;
  if (*fn_in == 0) return 0;

  if ((fs= hyx_make_segment (app_segments, fn_in, (char *) 0,
             &index_number, FSop_update, 0L, 0x7FFFFFFEL))
      == (struct FILE_SEGMENT *) 0) return -1;

  for (; fs->FS_next != (struct FILE_SEGMENT *) 0; fs= fs->FS_next);
  app_segments= &fs->FS_next;
  t2d++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int explicit_segment_specification (char *ex)
{
  struct FILE_SEGMENT *fs;

  if (hyx_setup_segment (app_segments, &fs, ex, &index_number) != 0)
    return -1;

  for (fs= *app_segments;
       fs->FS_next != (struct FILE_SEGMENT *) 0;
       fs= fs->FS_next);

  app_segments= &fs->FS_next;
  t2d++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int stdin_segment_specification (char *frame_name)
{
  struct FILE_SEGMENT *fs;

  if (hyx_setup_stdin_segment (app_segments, &fs, frame_name,
                               &index_number) != 0)
    return -1;

  for (fs= *app_segments;
       fs->FS_next != (struct FILE_SEGMENT *) 0;
       fs= fs->FS_next);

  app_segments= &fs->FS_next;
  t2d++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int deletion_segment (char *frnm)
{
  struct FILE_SEGMENT *fs;

printf ("deletion_segment: frnm='%s'\n", frnm);
  if (hyx_setup_delete_segment (app_segments, &fs, frnm, &index_number) != 0)
    return -1;

  for (fs= *app_segments;
       fs->FS_next != (struct FILE_SEGMENT *) 0;
       fs= fs->FS_next);

  app_segments= &fs->FS_next;
  t2d++;

  return 0;
}

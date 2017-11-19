/*
 *  FILE %ds/lmd5/lm5.c
 *
 *  template, standard command interpreter style
 *  - HELP
 *  - prototypes
 *
 *  written:       1992 02 19
 *  latest update: 1996-05-05 11:41:49
 *  $Id: lm5.c,v 1.2 2011/05/31 16:35:28 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/lmd5.h>
#include <gg/filename.h>

#define STDHLP stdout
#ifdef MSDOS
#define ARG_C_max 24
#else
#define ARG_C_max 240
#endif
static char *arg_v [ARG_C_max];
static int arg_c= 0;

/* Quick Hack: ------------------------------------------------------------ */
#ifdef MSDOS
#define SUBDIRS                         /* Rekursive Suche durch das        */
                                        /* Filesystem moeglich              */
#define BETTER_FILENAME_MATCH           /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
static char filenm [66];
static int verbose_mode= 0;

#define PMODE_NONE      0
#define PMODE_STREAM    1
static int processing_mode= PMODE_STREAM;

static struct LMD5_CONTROL *lm5_control= (struct LMD5_CONTROL *) 0;
static char *lm5_outfile= "@lm5out.dmp";

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: lm5 [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
#ifdef SUBDIRS
  "  -s -r ... subdirs\n",
#endif
  "  -v ... verbose mode\n",
  "EXAMPLES:\n",
  "\n",
  "(@)Alm5.c 0.01 #D$1996-04-14  9:46:43\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  char *arg;
  int i, j;

  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'f': case 'F':
          if (arg [2] == 0) break;
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= arg ;
          break;

#ifdef SUBDIRS
        case 'r': case 'R':
        case 's': case 'S':
#endif
        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
#ifdef SUBDIRS
              case 'r': case 'R':
              case 's': case 'S':
                wcrd_set_subdirs (1);
                break;
#endif
              case 'v': case 'V':
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg[j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= arg;
  }

  if (arg_c)
  {
    /* preparations */
    if ((lm5_control= lmd5_create_control (lm5_outfile, 1))
         == (struct LMD5_CONTROL *) 0)
    {
      fprintf (stderr, "error: can't create control handle!\n");
      goto STOP;
    }

    for (i= 0; i < arg_c; i++)
    {
      arg= arg_v [i];

      if (arg [0] == '-')
      {
        if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not opened!\n", arg+2);
          break;
        }

        for (;;)
        {
          fscanf (fi2, "%s", filenm);
          if (feof (fi2)) break;
#ifdef SUBDIRS
          if (wcrd_wildcards_or_rec (filenm) == -1)
          {
            fclose (fi2);
            goto STOP;
          }
#else
          wcrd_wildcards (filenm);
#endif
        }
        fclose (fi2);
      }
      else
      {
#ifdef SUBDIRS
        if (wcrd_wildcards_or_rec (arg) == -1) goto STOP;
#else
        wcrd_wildcards (arg);
#endif
      }
    }

    /* wrapup */
    irdb_diag (stdout, lm5_control->LMD5_db);
    irdb_commit (lm5_control->LMD5_pos);
    /**** irdb_dump_to_file (lm5_outfile, lm5_control->LMD5_db); ****/
    irdb_diag (stdout, lm5_control->LMD5_db);

{
char *slots [10];
slots [0]= "wordcount";
slots [1]= "mausi";
slots [2]= "cnt";
slots [3]= "total";
irdb_post_increment_long (lm5_control->LMD5_pos, slots, 4, 17L);

slots [1]= "schnucki";
irdb_post_increment_long (lm5_control->LMD5_pos, slots, 4, 17L);
}

    lmd5_set_info_attribute_value (lm5_control, "schnucki", "mucki");

    irdb_diag (stdout, lm5_control->LMD5_db);
    irdb_commit (lm5_control->LMD5_pos);
  }

STOP:
  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  FILE *fi;

  if ((fi= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fn);
    return -2;
  }

  switch (processing_mode)
  {
    case PMODE_STREAM:
      lmd5_process_stream (lm5_control, fi);
      break;

    default:
      fprintf (stderr, "illegal processing mode %d for '%s'\n", processing_mode, fn);
      break;
  }

  fclose (fi);

  return 0;
}

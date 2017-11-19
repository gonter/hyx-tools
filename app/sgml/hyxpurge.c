/*
 *  FILE %sgml/hyxpurge.c
 *
 *  purge hypertext clusters
 *  - HELP
 *  - prototypes
 *
 *  written:       1991 02 16
 *                 1992 12 07: revision
 *  latest update: 1995-11-19
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <io.h>
#include <conio.h>
#else
#include <unistd.h>
#endif
#include <gg/hytxt.h>
#include <gg/filename.h>
#include <gg/sbr.h>
#include <gg/dpp.h>

#define REAL_AUTHOR
#define  STDHLP stderr
#ifdef MSDOS
#define ARG_C_max 24
#else
#define ARG_C_max 240
#endif
static char *arg_v [ARG_C_max];
static int arg_c= 0;

/* Quick Hack: ------------------------------------------------------------ */
#ifdef MSDOS
#define SUBDIRS                         /* Rekusive Suche durch das         */
                                        /* Filesystem moeglich              */
#define BETTER_FILENAME_MATCH           /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
#define FILENM_SIZE 1024
static char filenm [FILENM_SIZE];
static int verbose_level= 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: hyxpurge [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
#ifdef SUBDIRS
  "  -s -r ... subdirs\n",
#endif
  "  -v ... verbose mode\n",
  "EXAMPLES:\n",
  "\n",
  "(@)Ahyxpurge.c 1.18 #D$1995-11-19 12:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  char *afn;

  if (argc <= 1) goto HLP;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-')
         switch (argv [i][1])
         {
           case 'f': case 'F':
             if (argv [i][2] == 0) break;
               if (arg_c+1 < ARG_C_max)
                 arg_v [arg_c++] = argv [i];
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
              arg_v [arg_c++]= argv [i];

  if (arg_c)
  {
    int rc;

    for (i= 0; i < arg_c; i++)
      if (arg_v [i][0] == '-')
      {
        if ((afn= translate_logic_filename (&arg_v[i][2])) == (void *) 0)
          afn= &arg_v [i][2];
        if ((fi2= fopen (afn, "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not found!\n", &arg_v [i][2]);
          break;
        }

        for (;;)
        {
          rc= fread_line (fi2, filenm, FILENM_SIZE);
          if (rc <= 0 && feof (fi2)) break;
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
           if (wcrd_wildcards_or_rec (arg_v [i]) == -1) goto STOP;
#else
           wcrd_wildcards (arg_v [i]);
#endif
      }
  }

#ifdef SUBDIRS
STOP:
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *hyx_in)
{
  return hyx_purge (hyx_in, verbose_level);
}

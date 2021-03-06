/*
 *  FILE %ds/zip/zs.c
 *
 *  template, standard command interpreter style
 *
 *  written:       1992 02 19
 *  latest update: 1995-12-25
 *  $Id: zs.c,v 1.2 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/zip.h>

#define STDHLP stderr
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

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: zs [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
#ifdef SUBDIRS
  "  -s -r ... subdirs\n",
#endif
  "  -v ... verbose mode\n",
  "\n",
  "(@)Azs.c 0.01 #D$1995-12-26  2:07:52\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;

  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'f': case 'F':
          if (argv [i][2] == 0) break;
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= argv [i];
          break;

#ifdef SUBDIRS
        case 'r': case 'R':
        case 's': case 'S':
#endif
        case 'v': case 'V':
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
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", argv[i][j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= argv [i];

  if (arg_c)
  {
    for (i= 0; i < arg_c; i++)
      if (arg_v [i][0] == '-')
      {
        if ((fi2= fopen (& arg_v [i][2], "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not opened!\n", &arg_v [i][2]);
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
        if (wcrd_wildcards_or_rec (arg_v [i]) == -1) goto STOP;
#else
        wcrd_wildcards (arg_v [i]);
#endif
      }
  }
  else
  {
#ifdef SUBDIRS
    wcrd_wildcards_or_rec ("*.*");
#else
    main_fnc ("Default.fil");
#endif
  }

STOP:
  return 0;
}


/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  struct ZIP_CONTROL *zip_control;

  if ((zip_control= zip_init_control (fn)) != (struct ZIP_CONTROL *) 0)
  {
    zip_scan (zip_control);
    zip_quick_scan (fn);
    /** zip_delete_control (zip_control); **/
  }
  else
  {
    printf ("cant create zip_control for %s\n", fn);
  }

  return 0;
}

#define MAIN
#include "zip_0007.c"


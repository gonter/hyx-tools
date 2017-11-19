/*
 *  FILE ~/usr/gophtool/msrv.c
 *
 *  template, standard command interpreter style
 *  -  HELP
 *  -  t2d
 *  -  Menu
 *
 *  written:       1994-06-18
 *  latest update: 1995-04-30
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MSDOS
#include <conio.h>
#include <gg/filename.h>
#define syslog fprintf
#define LOG_INFO stderr
#else
#include <syslog.h>
#include <unistd.h>
#endif
#include <gg/sbr.h>
#include "msrvh.h"

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
#define BETTER_FILENAME_MATCH           /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
#define FILENM_SIZE 1024
static char filenm [FILENM_SIZE];
static int verbose_mode= 0;
static int my_pid= 4711;

static struct MSRV_defaults *Mdef= (struct MSRV_defaults *) 0;

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: msrv [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<filename> ... list of files\n",
  "  -v ... verbose mode\n",
  "  -d<fnm> ... read default settings from file; *** required ***\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Amsrv.c 1.05 #D$1995-04-27 09:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv []);
int main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;

  if (argc <= 1) goto HLP;

#ifndef MSDOS
  my_pid= getpid ();
#endif

  syslog (LOG_INFO, "msrv [%d]: starting up\n", my_pid);

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 0:
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= "-";
          break;
        case 'd': case 'D':
          Mdef= msrv_get_defaults (&argv[i][2]);
          break;
        case 'f': case 'F':
          if (argv [i][2] == 0) break;
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++]= argv [i];
          break;

        case 'v': case 'V':
          for (j=1; argv [i][j]; j++)
            switch (argv [i][j])
            {
              case 'v': case 'V':
                verbose_mode= 1;
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

  if (Mdef == (struct MSRV_defaults *) 0)
  {
    fprintf (stderr, "no configuration file, can't proceed!\n");
    return 0;
  }
  printf ("database='%s'\n", Mdef->MD_database);

  if (arg_c)
  {
    int rc;

    for (i= 0; i < arg_c; i++)
      if (arg_v [i][0] == '-' && arg_v [i][1] != 0)
      {
        if ((fi2= fopen (& arg_v [i][2], "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not opened!\n", &arg_v [i][2]);
          break;
        }
        for (;;)
        {
          rc= fread_line (fi2, filenm, FILENM_SIZE);
          if (rc <= 0 && feof (fi2)) break;
          wcrd_wildcards (filenm);
        }
        fclose (fi2);
      }
      else
      {
        wcrd_wildcards (arg_v [i]);
      }
  }
  else
  {
    main_fnc ("Default.fil");
  }

  syslog (LOG_INFO, "msrv [%d]: shutting down\n", my_pid);
  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  FILE *fi;

  if ((fi= (strcmp (fn, "-") == 0)
           ? (FILE *) stdin
           : fopen (fn, "rb"))
      == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fn);
    return -2;
  }

  msrv_process_requests (fi, Mdef);
  if (strcmp (fn, "-") != 0) fclose (fi);

  return 0;
}

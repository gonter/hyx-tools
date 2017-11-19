/*
 *  FILE /usr/inc/XXXX.c
 *
 *
 *  1992 02 19
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <gg/filename.h>

# define  STDHLP stderr
#ifdef MSDOS
# define  ARG_C_max       24
#else
# define  ARG_C_max      240
#endif
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

/* Quick Hack: ------------------------------------------------------------ */
#ifdef MSDOS
# define SUBDIRS                        /* Rekusive Suche durch das         */
                                        /* Filesystem m”glich               */
# define BETTER_FILENAME_MATCH          /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
static char filenm [66];
static int verbose_mode = 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: XXXX [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<filename> ... List of Files\n",
# ifdef SUBDIRS
  "  -s -r ... Subdirs\n",
# endif
  "  -v ... Verbose Mode\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)AXXXX.c 0.0 #D$1991-02-19 23:40:00\n",
  "\n",
# include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);

/* ------------------------------------------------------------------------ */
main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;

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

# ifdef SUBDIRS
           case 'r': case 'R':
           case 's': case 'S':
#endif
           case 'v': case 'V':
             for (j=1; argv [i][j]; j++)
               switch (argv [i][j])
               {
# ifdef SUBDIRS
                 case 'r': case 'R':
                 case 's': case 'S':
                   wcrd_set_subdirs (1);
                   break;
#endif
                 case 'v': case 'V':
                   verbose_mode = 1;
                   break;
                }
                break;

HLP:
# include <gg/help.inc>
         }
      else if (arg_c+1 < ARG_C_max)
              arg_v [arg_c++] = argv [i];

  if (arg_c)
  {
    for (i = 0; i < arg_c; i++)
      if (arg_v [i][0] == '-')
      {
        if (access  (& arg_v [i][2], 0) != 0)
        {
          fprintf (stderr, "File %s not found!\n", &arg_v [i][2]);
          break;
        }
        fi2 = fopen (& arg_v [i][2], "rt");
        for (;;)
        {
          fscanf (fi2, "%s", filenm);
          if (feof (fi2)) break;
# ifdef SUBDIRS
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
#define LB_SIZE 1024
static char line1 [LB_SIZE];
static char out_name [66];
static int out_count=1;

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  FILE *fi;
  FILE *fo=(FILE *) 0;
  long linecnt;

  if (access (fn, 0) != 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2;
  }

  printf ("reading from %s\n", fn);
  fi = fopen (fn, "rb");
  for (linecnt=0L;; linecnt++)
  {
    if (fgets (line1, LB_SIZE, fi) == (char *) 0
       || feof (fi)) break;
    if (fo == (FILE *) 0)
    {
      sprintf (out_name, "splt%04d.div", out_count++);
      printf ("writing to %s\n", out_name);
      fo = fopen (out_name, "wb");
    }
    if (fo == (FILE *) 0)
    {
      fprintf (stderr, "error creating an output file\n");
      break;
    }
    fputs (line1, fo);
    if ((linecnt % 1000L) == 999L)
    {
      if (fo != (FILE *) 0) fclose (fo);
      fo = (FILE *) 0;
    }
  }
  fclose (fi);
  if (fo != (FILE *) 0) fclose (fo);

  return 0;
}

/*
 *  FILE /usr/lex/lext.c
 *
 *
 *  1992 02 19
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <gg/filename.h>

#define  STDHLP stderr
#ifdef MSDOS
#define  ARG_C_max       24
#else
#define  ARG_C_max      240
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
static int verbose_mode = 0;
static char filenm [66];

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: lext [options] {file name}\n",
  "  split file according to first char of lexicon entry\n",
  "OPTIONS:\n",
  "  -f<filename> ... List of Files\n",
# ifdef SUBDIRS
  "  -s -r ... Subdirs\n",
# endif
  "  -v ... Verbose Mode\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Alext.c 1.0 #D$1992-02-23 11:00:00\n",
  "\n",
# include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);
int cdecl xxconvent (char *lps, char *lpd);

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
static char line_buffer1 [LB_SIZE];
static char line_buffer2 [LB_SIZE];

static char fo_seg_p[]="??????????";

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  FILE *fi;
  FILE *fo=(FILE *) 0;
  FILE *foe=(FILE *) 0;
  int  ch1;
  char fo_name [66];
  char *cp;
  char *fo_seg;
  long lc=0;

  if (access (fn, 0) != 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2;
  }

  fi = fopen (fn, "r");
  for (;;)
  {
    cp=fgets (line_buffer1, LB_SIZE, fi);
    if (feof (fi)) break;
    if (cp == (char *) 0) break;
    lc++;

    if (xxconvent (line_buffer1, line_buffer2) <= 0)
    {
      if (foe == (FILE *) 0)
      {
        foe = fopen ("error", "a");
        fprintf (stderr, "openening error!\n");
      }
      fprintf (foe, "%s(%ld) ", fn, lc);
      fputs (line_buffer1, foe);
      continue;
    }

    /* check out output segment */
    ch1 = line_buffer2[0];
    fo_seg="sy";
    if (ch1 >= 'a' && ch1 <= 'z')
    {
      fo_seg = "la";
      fo_seg[1]=(char) ch1;
    }
    if (ch1 >= 'A' && ch1 <= 'Z')
    {
      fo_seg = "ua";
      fo_seg[1]=(char) ch1-'A'+'a';
    }
    if (ch1 >= '0' && ch1 <= '9') fo_seg = "nu";
    if (ch1 == '&') fo_seg = "en";

    if (strcmp (fo_seg, fo_seg_p) != 0)
    {
      if (fo != (FILE *) 0) fclose (fo);
      strcpy (fo_name, &fn[2]);        /* ############################ */
      fo_name [4]=0;
      sprintf (&fo_name[strlen(fo_name)], "wg%s", fo_seg);
      fprintf (stderr, "opening file %s for output\n", fo_name);
      fo = fopen (fo_name, "a");
      if (fo == (FILE *) 0)
      {
        fprintf (stderr, "can't open file %s for output!\n", fo_name);
        goto STOP;
      }
    }
    strcpy (fo_seg_p, fo_seg);

    fputs (line_buffer2, fo);
    fputc ('\n', fo);
    if ((lc % 1000) == 0) fprintf (stderr, "record %8ld\n", lc);
  }

STOP:
  if (fo != (FILE *) 0) fclose (fo);
  if (foe != (FILE *) 0) fclose (foe);
  fclose (fi);

  return 0;
}

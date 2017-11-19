/*
 *  FILE /usr/lex/lext1.c
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
#include <gg/ytree.h>
#include <gg/dpp.h>

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
/* # define SUBDIRS  */                 /* Rekusive Suche durch das         */
                                        /* Filesystem m”glich               */
# define BETTER_FILENAME_MATCH          /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */
#else
#define wcrd_wildcards main_fnc
#endif

/* ------------------------------------------------------------------------ */
static char filenm [66];
static int verbose_mode = 0;
static int max_lng=3;
static int syl_lng=3;
static int syl_mode=0;
static int rev_mode=0;
static long syl_split=300L;
static struct YTREE *ytree=(struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: lext1 [options] {file name}\n",
  "  generate word prefix (or suffix) list from lexicon entries\n",
  "OPTIONS:\n",
  "  -f<filename> ... List of Files\n",
  "  -n<n> ... number of chars [DEF: 3]\n",
  "  -m<mode> ... mode [DEF: 0] 1=dynamic split up to <n>\n",
  "  -s<size> ... split_size [DEF: 300]\n",
  "  -r ... reverse input string\n",
  "  -v ... Verbose Mode\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Alext1.c 0.0 #D$1992-02-19 23:40:00\n",
  "\n",
# include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn);
int cdecl xmain_fnc (char *fn);
long cdecl t1_dump (char *fno);

/* ------------------------------------------------------------------------ */
main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;

  if (argc <= 1) goto HLP;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         {
           case 'f': case 'F':
             if (argv [i][2] == 0) break;
               if (arg_c+1 < ARG_C_max)
                 arg_v [arg_c++] = argv [i];
             break;
           case 'n': case 'N':
             sscanf (&argv[i][2], "%d", &max_lng);
             syl_lng = max_lng;
             break;
           case 'm': case 'M':
             sscanf (&argv[i][2], "%d", &syl_mode);
             break;
           case 's': case 'S':
             syl_split = get_parameter_value (&argv[i][2]);
             break;

           case 'r': case 'R':
           case 'v': case 'V':
             for (j=1; argv [i][j]; j++)
               switch (argv [i][j])
               {
                 case 'r': case 'R':
                   rev_mode= 1;
                   break;
                 case 'v': case 'V':
                   verbose_mode= 1;
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

  t1_dump ("$t1_dmp$.lut");

#ifdef SUBDIRS
STOP:
#endif
  return 0;
}

/* ------------------------------------------------------------------------ */
#define LB_SIZE 1024
static char line1 [LB_SIZE];

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  int rc;

  switch (syl_mode)
  {
    case 0:
      syl_lng = max_lng;
      return xmain_fnc (fn);
    case 1:
      for (syl_lng = 1; syl_lng <= max_lng; syl_lng++)
      {
        rc= xmain_fnc (fn);
        if (rc < 0) return rc;
        if (rc == 1) return 0;
      }
      printf ("further splitting would be possible\n");
      return 0;
  }
}

/* ------------------------------------------------------------------------ */
int xmain_fnc (char *fn)
{
  FILE *fi;
  struct YTREE *yt;
  int i;
  int ch;
  char *line2;
  int rv=1;

  if (access (fn, 0) != 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2;
  }

  printf ("reading from file %s; syl=%d max_syl=%d\n", fn, syl_lng, max_lng);
  fi = fopen (fn, "r");
  for (;;)
  {
    if (fgets (line1, LB_SIZE, fi) == (char *) 0) break;
    if (feof (fi)) break;
    line2=&line1[12];
    for (i=strlen(line2)-1; i>=0; i--)
    {
      ch = line2[i] & 0x00FF;
      if (ch == 0x0D) line2[i]=0; else
      if (ch == 0x0A) line2[i]=0; else break;
    }
    if (rev_mode) strrev (line2);

    line2[syl_lng]=0;
    if (syl_mode == 1 && strlen (line2) > 1)
    {
      if (strlen (line2) < syl_lng) continue;
      ch= line2[syl_lng-1] & 0x00FF;
      line2[syl_lng-1]= 0;
      yt= ytree_lookup_word (ytree, line2);
      if (yt == (struct YTREE *) 0
         || yt->YT_info <= syl_split) continue;
      line2[syl_lng-1]= (char) ch;
    }

    yt= ytree_insert_word (&ytree, line2);
    if (yt == NIL)
    {
      printf ("*** creating ytree: can't insert %s\n", line2);
      break;
    }
    yt->YT_flags |= YTflag_EOW;
    yt->YT_info++;
    if (yt->YT_info > syl_split) rv=0;
  }
  fclose (fi);

  return rv;
}

/* ------------------------------------------------------------------------ */
long t1_dump (char *fno)
{
  FILE *fo;
  long unique;

  fo = fopen (fno, "wb");
  if (fo == (FILE *) 0) return -1L;

  printf ("dumping to file %s ...", fno);
  ytree_size (ytree);
  unique = ytree_dump (fo, ytree);
  printf (" %ld unique\n", unique);
  fclose (fo);

  return unique;
}

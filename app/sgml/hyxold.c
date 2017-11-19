/*
 *  FILE %sgml/hyxold.c
 *
 *  *** OBSOLETE ***, at least more or less ...
 *
 *  Purgen von Hypertext Files
 *  - HELP
 *
 *  written:       1990 02 16
 *  latest update: 1994-12-11 (1996-10-14  0:21:23)
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/hytxt.h>
#include <gg/filename.h>

#define STDHLP stderr
#define ARG_C_max       24
static char *arg_v [ARG_C_max];
static int arg_c= 0;

static char filenm [66];
static char line [512];

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static int action= 0;           /* 0 .. list contentents                    */
                                /* 1 .. purge old version                   */

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: hyx [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm>  ... List of Files\n",
  "  @[<fnm>] ... Execute HYX Script\n",
  "  -p[<m>]       ... Purge\n",
  "    <m> frame seperator:\n",
  "    DEF ... no seperator [DEF]\n",
  "    n   ... Newline: CR LF\n",
  "  -s -r         ... Subdirs\n",
  "  -v            ... Verbose Mode\n",
  "(@)Ahyx.c 1.15 #D$1994-12-11 20:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
main (argc, argv)
int  argc;
char *argv [];
{ FILE *fi2;
  int i, j;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         {
           case 'f': case 'F':
                     if (argv [i][2] == 0) break;
                     if (arg_c+1 < ARG_C_max)
                        arg_v [arg_c++] = argv [i];
                     break;

           case 'r': case 'R':
           case 's': case 'S':
           case 'v': case 'V':
                     for (j=1; argv [i][j]; j++)
                        switch (argv [i][j])
                        {
                          case 'r': case 'R':
                          case 's': case 'S':
                            wcrd_set_subdirs (1);
                            break;
                          case 'v': case 'V':
                            verbose_mode++;
                            break;
                        }
                     break;

           case 'p': case 'P':
                     action=1;
                     switch (argv [i][2])
                     {
                       case 'n': case 'N':
                         hytxt_purge_seperator ("\x0D\x0A", 2);
                         break;
                       default:
                         hytxt_purge_seperator ((char *) 0, 0);
                         break;
                     }
                     break;

HLP:
#include <gg/help.inc>
         }
      else {
             if (arg_c+1 < ARG_C_max)
                arg_v [arg_c++] = argv [i];
           }

  if (arg_c)
  {
    for (i = 0; i < arg_c; i++)
    {
      if (arg_v [i][0] == '-')
      {
        if ((fi2= fopen (&arg_v [i][2], "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not found!\n", &arg_v [i][2]);
          break;
        }
        for (;;)
        {
          fscanf (fi2, "%s", filenm);
          if (feof (fi2)) break;
          if (wcrd_wildcards_or_rec (filenm) == -1)
          {
            fclose (fi2);
            goto STOP;
          }
        }
        fclose (fi2);
      }
      else
      {
        if (arg_v [i][0] == '@') hyx_script (&arg_v [i][1]);
        else
        {
          if (wcrd_wildcards_or_rec (arg_v [i]) == -1) goto STOP;
        }
      }
    }
  }
  else hyx_script ("");

STOP:
  return 0;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  struct HYTXT_FRAME *hyt;

  switch (action)
  {
    default:
    case  0:
      hyx_engine_list (stdout, fn, &hyt, 0, 0x0003, 2, 0x0003);
      break;
    case  1:
      hy_purge (fn, 0);
      break;
  }
}

/* ------------------------------------------------------------------------ */
hyx_script (char *fn)
{
  FILE *fi;
  int fi_open= 0;
  int rv;
  char *QUIT= "quit";

  if (*fn == 0)
  {
    printf ("HYX Script shell ready\n");
  }
  else
  {
    if ((fi= fopen (fn, "rt")) == (FILE *) 0)
    {
      fprintf (stderr, "Script File %s not opened!\n", fn);
      return -1;
    }
    fi_open= 1;
  }

  for (;;)
  {
    if (fi_open)
    {
      fscanf (fi, "%[^\n]", line);
      if (feof (fi))
      {
        strcpy (line, QUIT);
        break;
      }
      fgetc (fi);
    }
    else
    {
      printf ("$ ");
      scanf ("%[^\n]", line);
      getchar ();
    }

    rv= hyx_engine_command (line);
    if (rv == 499) break;
  }

  return 0;
}

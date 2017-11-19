/*
 *  FILE XXXX.c
 *
 *
 *  1988 11 17
 *
 */

# include <stdio.h>
# include <gg/fnames.h>


# define  STDHLP stderr
# define  ARG_C_max       24
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

# define XXXX xxxx      /* Name der Programmfunktion */

static char filenm [64];

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{ "USAGE:     XXXX [options] {file name}\n",
  "OPTIONS:   -f<filename> ... List of Files\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)AXXXX.c 0.0 #D$1989-02-14 15:45:00\n",
  "\n",
# include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
main (argc, argv)
int  argc;
char *argv [];
{ FILE *fi2;
  int i, j;
  int sgml_filter_tag_beg (),  xsgml_tag_begin (),
      sgml_filter_tag_end (),  xsgml_tag_end   (),
      sgml_filter_tag_chr (),
      sgml_filter_chr     (),  xout_char       ();

  patch (sgml_filter_tag_beg, xsgml_tag_begin);
  patch (sgml_filter_tag_end, xsgml_tag_end);
  patch (sgml_filter_tag_chr, xout_char);
  patch (sgml_filter_chr,     xout_char);
  sgml_filter_reset ();

  if (argc <= 1) goto HLP;
  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         { case 'f': case 'F':
                     if (argv [i][2] == 0) break;
                     if (arg_c+1 < ARG_C_max)
                        arg_v [arg_c++] = argv [i];
                     break;

           case 'a': case 'A':
HLP:
# include <gg/help.inc>
         }
      else if (arg_c+1 < ARG_C_max)
              arg_v [arg_c++] = argv [i];

  if (arg_c)
     for (i = 0; i < arg_c; i++)
         if (arg_v [i][0] == '-')
            {
                     if (access  (& arg_v [i][2], 0) != 0)
                        { fprintf (stderr, "File %s not found!\n",
                                   &arg_v [i][2]);
                          break;
                        }
                     fi2 = fopen (& arg_v [i][2], "rt");
                     for (;;)
                     { fscanf (fi2, "%s", filenm);
                       if (feof (fi2)) break;
                       wildcards (filenm);
                     }
                     fclose (fi2);
           }
       else wildcards (arg_v [i]);
  else XXXX ("Default.fil");

  return 0;
}

/* ------------------------------------------------------------------------ */
wildcards (fn)
char *fn;
{ char *nm; int wild=0;
  for (nm=fn; *nm && !wild; nm++)
      if (*nm == '*' || *nm == '?') wild=1;
  if (wild)
     while ((nm=Fname_find (fn, FA_FILE)) != (char *) 0)
           XXXX (nm);
  else XXXX (fn);
}

/* ------------------------------------------------------------------------ */
XXXX (fn)
char *fn;
{ FILE *fi;
  int  ch;

  if (access (fn, 0) != 0)
     { fprintf (stderr, "File %s not found!\n", fn);
       return -1;
     }
  fi = fopen (fn, "rt");
  for (;;)
  { ch = fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    sgml_filter (ch);
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */

xout_char (ch)
int ch;
{
  fputc (ch, stdout);
}

xsgml_tag_begin ()
{
  printf ("®");
}

xsgml_tag_end ()
{
  printf ("¯");
}


/*
 *  FILE c:/usr/sbr/tt.c
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
static char line [400];

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
  int lng;
  long hash;

  if (access (fn, 0) != 0)
     { fprintf (stderr, "File %s not found!\n", fn);
       return -1;
     }
  fi = fopen (fn, "rt");
  for (;;)
  {
    fscanf (fi, "%[^\n]", line);
    if (feof (fi)) break; fgetc (fi);
    lng = strlen (line);
#define X2
#ifdef X1
    printf ("\n-------------------\n%s\n", line);
    string_hash_1 (line, lng, &hash);
    printf ("Var 1: %3d %8lX\n", lng, hash);
    string_hash_2 (line, lng, &hash);
    printf ("Var 2:     %8lX %4.4s\n",      hash, hash);
    string_hash_3 (line, lng, &hash);
    printf ("Var 3:     %8lX\n",      hash);
    string_hash_4 (line, lng, &hash);
    printf ("Var 4:     %8lX\n",      hash);
    string_hash_5 (line, lng, &hash);
    printf ("Var 5:     %8lX\n",      hash);
    string_hash_6 (line, lng, &hash);
    printf ("Var 6:     %8lX\n",      hash);
#endif
#ifdef X2
    string_hash_1 (line, lng, &hash);
    printf ("%3d %8lX ", lng, hash);
    string_hash_2 (line, lng, &hash);
    printf ("%08lX ",      hash, hash);
    string_hash_3 (line, lng, &hash);
    printf ("%8lX ",      hash);
    string_hash_4 (line, lng, &hash);
    printf ("%8lX ",      hash);
    string_hash_5 (line, lng, &hash);
    printf ("%8lX ",      hash);
    string_hash_6 (line, lng, &hash);
    printf ("%8lX %s\n",      hash, line);
#endif
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
int string_hash_1 (str, lng, hash)
char   *str;
int     lng;
long   *hash;
{ int i;
  long h=0L;
  for (i=0; i<lng; i++)
      h += (long) str [i];
  *hash=h;
}

/* ------------------------------------------------------------------------ */
int string_hash_2 (str, lng, hash)
char   *str;
int     lng;
char   *hash;
{ int i;
  for (i=0;i<4;i++) hash [i]=0;
  for (i=0; i<lng; i++)
      hash [i%4] += str [i];
}

/* ------------------------------------------------------------------------ */
int string_hash_3 (str, lng, hash)
char   *str;
int     lng;
long   *hash;
{ int i;
  long h=0L;
  for (i=0; i<lng; i++)
      h += ((long) str [i]) * ((long) i+1);
  *hash=h;
}

/* ------------------------------------------------------------------------ */
int string_hash_4 (str, lng, hash)
char   *str;
int     lng;
long   *hash;
{ int i;
  long h=0L, l=1L;
  for (i=0; i<lng; i++)
      h += l * (l= (long) str [i]);
  *hash=h;
}

/* ------------------------------------------------------------------------ */
int string_hash_5 (str, lng, hash)
char   *str;
int     lng;
long   *hash;
{ int i;
  long h=0L, l=1L;
  for (i=0; i<lng; i++)
      h += l * (l= (long) str [i]) * ((long) i+1);
  *hash=h;
}

/* ------------------------------------------------------------------------ */
int string_hash_6 (str, lng, hash)
char   *str;
int     lng;
long   *hash;
{ int i;
  long h=1L;
  for (i=0; i<lng; i++)
      h *= (long) str [i];
  *hash=h;
}





/*
 *  FILE C:\usr\sbr\strings.c
 *
 *  Testmodule fuer String-Operationen
 *
 *  1989 05 21
 *
 */

# include <stdio.h>

# define  STDHLP stderr
# define  ARG_C_max       24
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

static char filenm [64];

# ifdef NIL
# undef NIL
# endif
# define NIL (char *) 0

# define MAX_LINE 256
static char
  line0 [MAX_LINE],
  line1 [MAX_LINE],
  line2 [MAX_LINE],
  line3 [MAX_LINE];

static char
  *linep0,
  *linep1,
  *linep2,
  *linep3;

static int  int1, int2, int3, int4;

/* ------------------------------------------------------------------------ */
extern long
  strcmp        (),
  strncmp       (),
  strcmp_c      (),
  strcmp_ebcdic (),
  strcpy        (),
  strnscpy      (),
  match_lng     ();

/* ------------------------------------------------------------------------ */
struct TEST_ARRAY
{
  char *name;
  long (*funct) ();
  int   inp_str;
  int   inp_int;
  int   out_str;
  int   out_int;
  int   rval;           /* 0 -> void; 1 -> int; 2 -> char * */
} ;

struct TEST_ARRAY test_array [] =
{
  { "strcmp",   strcmp,         0x0003, 0x0000, 0x0000, 0x0000, 1 },
  { "strncmp",  strncmp,        0x0003, 0x0004, 0x0000, 0x0000, 1 },
  { "strcpy",   strcpy,         0x0002, 0x0000, 0x0001, 0x0000, 2 },
  { "strnscpy", strnscpy,       0x0002, 0x0004, 0x0001, 0x0000, 0 },
  { "strcmp_c", strcmp_c,       0x0003, 0x0000, 0x0000, 0x0000, 1 } ,
  { "strcmp_ebcdic", strcmp_ebcdic, 0x0003, 0x0000, 0x0000, 0x0000, 1 },
  { "match_lng", match_lng,     0x0003, 0x0004, 0x0000, 0x0000, 1 }
} ;

static int array_size;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{ "USAGE:     strings [options] {file name}\n",
  "OPTIONS:   -f<filename> ... List of Files\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Astrings.c 0.0 #D$1989-02-14 15:45:00\n",
  "\n",
# include "c:\usr\inc\public.inc"
} ;

/* ------------------------------------------------------------------------ */
main (argc, argv)
int  argc;
char *argv [];
{ FILE *fi2;
  int i, j;

  array_size = sizeof (test_array) / sizeof (struct TEST_ARRAY);

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         {
           case 'f': case 'F':
                     if (argv [i][2] == 0) break;
                     if (arg_c+1 < ARG_C_max)
                        arg_v [arg_c++] = argv [i];
                     break;

           case 'a': case 'A':
HLP:
# include "c:\usr\inc\help.inc"
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
                     {
                       fscanf (fi2, "%s", filenm);
                       if (feof (fi2)) break;
                       strings (filenm);
                     }
                     fclose (fi2);
           }
       else strings (arg_v [i]);
  else strings_prompt ();

  return 0;
}

/* ------------------------------------------------------------------------ */
strings (fn)
char *fn;
{ FILE *fi;
  int  ch;

  if (access (fn, 0) != 0)
     { fprintf (stderr, "File %s not found!\n", fn);
       return -1;
     }
  fi = fopen (fn, "rt");
  for (;;)
  {
    ch = fgetc (fi);
    if (feof (fi)) break;
    fputc (ch, stdout);
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
strings_prompt ()
{
  int i, found;
  long rc;

  for (;;)
  {
    printf ("Command: "); scanf ("%[^\n]", line0); fgetc (stdin);
    if ((int) strcmp_c (line0, "exit") == 0) break;
    found = -1;
    for (i=0; i < array_size && found < 0; i++)
        if ((int) strcmp (line0, test_array [i].name) == 0)
           found=0;
    if (found==-1)
       {
         printf ("Function %s not known!\n", line0);
         continue;
       }
    if (test_array [found].inp_str & 0x0001)
       {
         printf ("Parameter 1 (String): ");
         scanf ("%[^\n]", line1); fgetc (stdin);
         linep1 = ((int) strcmp (line1, "NIL") == 0) ? NIL : line1;
       }
    if (test_array [found].inp_str & 0x0002)
       {
         printf ("Parameter 2 (String): "); 
         scanf ("%[^\n]", line2); fgetc (stdin);
         linep2 = ((int) strcmp (line2, "NIL") == 0) ? NIL : line2;
       }
    if (test_array [found].inp_int & 0x0004)
       {
         printf ("Parameter 3 (Integer): ");
         scanf ("%d", &int3);
       }
    switch (test_array [found].inp_str |
            test_array [found].out_str)
    {
      case 0x0001:
           switch (test_array [found].inp_int)
           {
             case 0x0002:
                  rc = (test_array [found].funct) (linep1, int2);
                  break;
           }
           break;
      case 0x0003:
           switch (test_array [found].inp_int)
           {
             case 0x0000:
                  rc = (test_array [found].funct) (linep1, linep2);
                  printf ("%s (%s, %s) -: %d\n", line0, linep1, linep2, rc);
                  break;
             case 0x0004:
                  rc = (test_array [found].funct) (linep1, linep2, int3);
                  break;
           }
           break;
    }
    if (test_array [found].out_str & 0x0001)
       {
         printf ("Return Parameter 1 (String): %s\n", line1);
       }
    if (test_array [found].out_int & 0x0004)
       {
         printf ("Return Parameter 3 (Integer): %d\n", int3);
       }
    switch (test_array [found].rval)
    {
      case 0: printf ("Return Value is void.\n"); break;
      case 1: printf ("Return Value is int %d\n", (int) rc); break;
      case 2: printf ("Return Value is string %s\n", (char *) rc); break;
    }
  }
}


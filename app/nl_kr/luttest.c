/*
 *  FILE %nl_kr/luttest.c
 *
 *  Worte in LUT nachsehen
 *  -  HELP
 *
 *  written:       1989 04 17
 *  latest update: 2000-01-06 18:50:48
 *  $Id: luttest.c,v 1.3 2001/09/10 06:58:36 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/lookup.h>
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>

#define MAX_LINE 4096
static char line [MAX_LINE];

static int modus= 1;     /* 0 -> LUT im RAM, sonst -> LUT auf FILE */

static char *lut_file_name= (char *) 0;
static char tfb_file_name [256];
static struct LMDT_CONTROL *lmdt;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: luttest [options] {file name}\n",
  "OPTIONS:\n",
  "  -m ... LUT in memory (must be done before -l<fnm>)\n",
  "         [DEF: LUT will be on file}\n",
  "  -f<fnm> ... list of files\n",
  "  -l<fnm> ... lookup table (binary)\n",
  "  -t[<fnm>] ... optional TFB file\n",
  "\n",
  "(@)Aluttest.c 3.03 #D$2000-01-06 18:51:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl luttest (char *fn, void *cd);
void cdecl luttest_manual (void);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  char *arg;
  int i, j;
  int lut_eingelesen= 0;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
      || (lmdt= lmdt_control_new ()) == (struct LMDT_CONTROL *) 0)
  {
    fprintf (stderr, "fatal error: can't create control structure!!\n");
    return 1;
  }

  wcrd2_set_processor (wcrd, WCRD_set_file_processor, luttest, (void *) 0);
  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'f': case 'F':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;
        case 'm': case 'M':
          modus= 0;
          break;
        case 'l': case 'L':
          lut_file_name= arg+2;
          lmd_RL3 (lmdt, lut_file_name, modus);
          lut_eingelesen= 1;
          break;
        case 't': case 'T':
          if (arg [2] == 0)
          {
            if (lut_eingelesen == 0) goto HLP;
            fnmcpy (tfb_file_name, lut_file_name, ".tfb");
            lmd_RL3_set_tfb_file (lmdt, tfb_file_name);
          }
          else lmd_RL3_set_tfb_file (lmdt, arg+2);
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  if (!lut_eingelesen) lmd_RL3 (lmdt, "xxx.lut", modus);

  if (array_elements (arguments))
  {
    wcrd2_arguments (wcrd, arguments);
  }
  else luttest_manual ();

  return 0;
}

/* ------------------------------------------------------------------------ */
int luttest (char *fn, void *cd)
{
  FILE *fi;

  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fn);
    return -1;
  }

  for (;;)
  {
    int lng;
    lng= fread_line (fi, line, MAX_LINE);
    if (lng <= 0 || feof (fi)) break;
    lmd_TWF (lmdt, line);
  }
  fclose (fi);
  return 0;
}

/* ------------------------------------------------------------------------ */
void luttest_manual ()
{ 
  for (;;)
  {
    printf ("Wort >");
    scanf  ("%s", line);

    if (feof (stdin)
        || line [0]=='\\'
        || strcmp (line, ".") == 0
       ) break;

    lmd_TWF (lmdt, line);
    if (strcmp (line, "quit") == 0) break;
  }
}

/*
 *  FILE %ds/bbc/bbct1.c
 *
 *  blackboard controller test
 *  -- incomplete --
 *
 *  written:       1996-08-11
 *  latest update: 1996-12-01 21:50:36
 *  $Id: bbct1.c,v 1.2 2003/06/25 03:09:53 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/filename.h>
#include <gg/fileio.h>
#include <gg/wildcard.h>
#include <gg/array.h>
#include <gg/sbr.h>
#include <gg/bbch.h>
#ifdef MSDOS
#include <conio.h>
#endif /* MSDOS */

#define STDHLP stderr

#define MAX_FILENM 80
static char filenm [MAX_FILENM];
static int verbose_mode= 0;

/* ------------------------------------------------------------------------ */
#define MAX_TEST_BUFFER 1024
static char test_buffer [MAX_TEST_BUFFER];
static struct BBC_SESSION *bbcs;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
#ifdef TO_UPPER
  "USAGE: bbct1 [options] {file name}\n",
#endif /* TO_UPPER */
#ifdef TO_LOWER
  "USAGE: bbct1 [options] {file name}\n",
#endif /* TO_LOWER */
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
  "  -r ... recursive\n",
  "  -v ... verbose: tell filename\n",
  "\n",
#ifdef TO_UPPER
  "(@)Atoupper.c 1.02 #D$1996-08-11 22:07:35\n",
#endif /* TO_UPPER */
#ifdef TO_LOWER
  "(@)Atolower.c 1.02 #D$1996-08-11 22:07:39\n",
#endif /* TO_LOWER */
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl bbc_test (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  int rc;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       bbc_test, (void *) 0);

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

        case 'r': case 'R':
        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
          {
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
            }
          }
          break;

        case 'a': case 'A':
HLP:
#include <gg/help.inc>
      }
      else array_push (arguments, (void *) arg);
  }

  if ((bbcs= bbc_new_session ()) == (struct BBC_SESSION *) 0)
  {
    fprintf (stderr, "could not establish BBC session\n");
    return 1;
  }

    bbcs->BBCS_key_file= ".kredenz.tfb";
    bbcs->BBCS_my_name= "bbct1";
    bbcs->BBCS_my_resource= "test1";
    bbcs->BBCS_public_resource= "test1";

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
  {
    if (arg [0] == '-')
    {
      if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
      {
        fprintf (stderr, "can't open file %s!\n", arg+2);
        break;
      }
      for (;;)
      {
        rc= fread_line (fi2, filenm, MAX_FILENM);
        if (feof (fi2)) break;
        wcrd2_wildcards (wcrd, filenm);
      }
      fclose (fi2);
    }
    else wcrd2_wildcards (wcrd, arg);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int bbc_test (char *fn, void *cd)
{
  FILE *fi;
  int rc;
  struct BBC_CONNECTION *bbc1;
  struct BBC_CONNECTION *bbc2;

  bbc1= bbc_init_connection (bbcs, 1);
  bbc2= bbc_init_connection (bbcs, 1);

#ifdef MSDOS
  cd;
#endif

  if (verbose_mode > 0) printf ("\n%s:\n", fn);
  if ((fi= fopen (fn, "rb")) == (FILE *) 0) return -1;

  for (;;)
  {
    rc= fread_line (fi, test_buffer, MAX_TEST_BUFFER);
    if (rc <= 0 && feof (fi)) break;

    test_buffer [rc++]= '\n';
    printf ("1: '%s'", test_buffer);
  }
  fclose (fi);
  return 0;
}

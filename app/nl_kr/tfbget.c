/*
 *  FILE %ds/tfb/tfbget.c
 *
 *  get entries from a tfb
 *  - HELP
 *
 *  written:       1995-10-20
 *  latest update: 1996-08-13 16:02:23
 *  $Id: tfbget.c,v 1.4 2005/03/11 23:58:28 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/sbr.h>
#include <gg/lookup.h>
#include <gg/array.h>
#include <gg/tfb.h>
#include <gg/filename.h>

#define STDHLP stdout

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static char filenm [MAX_FNM_LENGTH];

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: tfbget [options] filename keys*\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
  "  -r ... subdirs\n",
  "  -v ... verbose mode\n",
  "\n",
  "(@)Atfbget.c 1.14 #D$2005-03-12  0:56:54\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl tfb_set_name (char *fn);
int cdecl tfb_lookup_string (char *str);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  int i, j;
  char *arg;
  int rc;
  struct TFB_HANDLE *tfb_handle;
  struct ARRAY_CONTROL *arguments;

  if ((arguments= array_new ()) == (struct ARRAY_CONTROL *) 0) return 1;

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

        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'v': case 'V':
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg [j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  if (array_elements (arguments)
      && (tfb_handle= tfb_create_handle ((char *) array_shift (arguments),
                                         (char *) 0))
          != (struct TFB_HANDLE *) 0
     )
  {
    while ((arg= (char *) array_shift (arguments)) != (char *) 0)
    {
      if (arg [0] == '-')
      {
        if ((fi2= fopen (arg +2, "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not opened!\n", arg +2);
          break;
        }

        for (;;)
        {
          rc= fread_line (fi2, filenm, MAX_FNM_LENGTH);
          if (rc <= 0 && feof (fi2)) break;
          tfb_transfer_entry (stdout, tfb_handle, filenm);
        }
        fclose (fi2);
      }
      else
      {
        tfb_transfer_entry (stdout, tfb_handle, arg);
      }
    }
    tfb_close_handle (tfb_handle);
  }


  return 0;
}

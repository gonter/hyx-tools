/*
 *  FILE %usr/inc/temp.c
 *
 *  template, standard command interpreter style
 *  - HELP
 *  - prototypes
 *
 *  written:       1992 02 19
 *  latest update: 1996-09-24 11:08:41
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/dbx.h>

#define STDHLP stdout

static char *dbf_class= (char *) 0;
static int output_mode= 0;

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: XXXX [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
  "  -r ... subdirs\n",
  "  -v ... verbose mode\n",
  "EXAMPLES:\n",
  "\n",
  "(@)AXXXX.c 0.02 #D$1996-08-11 16:54:16\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl main_fnc (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  FILE *fi2;
  char *arg;
  int i, j;
  int rc;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;
#define MAX_FILENM 66
  char filenm [MAX_FILENM];
  int verbose_mode= 0;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor, main_fnc, (void *) 0);
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
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg[j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  if (array_elements (arguments))
  {
    while ((arg= (char *) array_shift (arguments)) != (char *) 0)
    {
      if (arg [0] == '-')
      {
        if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not opened!\n", arg+2);
          break;
        }

        for (;;)
        {
          rc= fread_line (fi2, filenm, MAX_FILENM);
          if (rc <= 0 && feof (fi2)) break;
          if (wcrd2_wildcards (wcrd, filenm) == -1)
          {
            fclose (fi2);
            goto STOP;
          }
        }
        fclose (fi2);
      }
      else
      {
        if (wcrd2_wildcards (wcrd, arg) == -1) goto STOP;
      }
    }
  }

STOP:
  return 0;
}

/* ------------------------------------------------------------------------ */
int dbx_dbf_puts (
FILE *fo,
struct DBX_FIELD_DESCRIPTOR *fdesc,
char *ptr)
{
  int i;
  int s;
  int ch;
  int x= 0;

  s= fdesc->size;
  for (i= 0; i < s; i++)
  {
    if ((ch= *ptr++ & 0x00FF) == 0) break;

    switch (x)
    {
      case 0:
        if (ch != ' ' && ch != '\t')
        {
          x= 1;
          fputc ('<', fo);
          fputs (fdesc->name, fo);
          fputc ('>', fo);
          fputc (ch, fo);
        }
        break;

      case 1:
        if (ch != ' ' && ch != '\t')
        {
          if (ch == ';')
          {
            x= 0;
            fputc ('\n', fo);
          }
          else
            fputc (ch, fo);
        }
        else
          x= 2;
        break;

      case 2:
        if (ch != ' ' && ch != '\t')
        {
          fputc (' ', fo);
          fputc (ch, fo);
          x= 1;
        }
    }
  }

  if (x) fputc ('\n', fo);
  return fdesc->size;
}

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn, void * cd)
{
  struct DBX_FILE_DESCRIPTOR *dbx;
  struct DBX_SCHEMA *schema;
  FILE *fi;
  char *buffer, *ptr;
  int rec_siz;
  int fld_cnt;
  int i;
  long num_rec= 0L;

#ifdef MSDOS
  cd;
#endif /* MSDOS */

  printf ("dbf: fnm='%s'\n", fn);

  if ((dbx= dbx_open_dbf (fn, dbf_class)) == (struct DBX_FILE_DESCRIPTOR *) 0
      || (fi= (FILE *) dbx->fi1) == (FILE *) 0
      || (schema= dbx->schema) == (struct DBX_SCHEMA *) 0
     )
    return -1;

  printf ("dbf: header read; header_size=%ld record_size=%ld\n",
          dbx->header_size, dbx->record_size);

  if (dbx->record_size >= 0x00010000L)
  {
    fprintf (stderr, "can't handle buffers with a size of %ld bytes!\n",
             dbx->record_size);
    return -1;
  }

  rec_siz= (int) dbx->record_size;
  fld_cnt= (int) schema->n_fields;

printf ("rec_siz=%d fld_cnt=%d\n", rec_siz, fld_cnt);

  if ((buffer= malloc (rec_siz)) == (char *) 0)
  {
    fprintf (stderr, "can't allocate buffer of %d bytes!\n", rec_siz);
    return -1;
  }

  fseek (fi, dbx->header_size, 0);

  for (i= 0; i < fld_cnt; i++)
  {
    to_lower (schema->fields[i]->name);
  }

  for (num_rec= 0L;; num_rec++)
  {
    fread (buffer, 1, rec_siz, fi);
    if (feof (fi)) break;

    switch (output_mode)
    {
      default:
        fputs ("<rec>\n", stdout);
        ptr= buffer;
        for (i= 0; i < fld_cnt; i++)
        {
          /*** if (i != 0) fputs ("<>", stdout); ***/
          ptr += dbx_dbf_puts (stdout, schema->fields [i], ptr);
          /*** fputc ('\n', stdout); ***/
        }
        fputs ("</rec>\n", stdout);
        break;
    }
  }

  printf ("%ld records processed!\n", num_rec);

  fclose (fi);
  dbx->fi1= (void *) 0;

  /* T2D: free complete dbx file descriptor!! */

  return 0;
}

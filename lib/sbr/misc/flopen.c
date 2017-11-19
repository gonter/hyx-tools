/*
 *  FILE %sbr/flopen.c
 *
 *  lazy file open
 *
 *  written:       1991 03 25
 *                 1994-10-10 was ~/usr/lexicon/dictadd5.c
 *                            Filecache System fuer Lexicon-Operationen
 *  latest update: 1996-10-10  0:38:07
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
struct FILECACHE
{
  struct FILECACHE *next;
  FILE *fp;
  char mode [8];
  char name [4];
} ;

static struct FILECACHE *filecache= (struct FILECACHE *) 0;

/* ------------------------------------------------------------------------ */
FILE *flopen (char *file_name, char *open_mode)
{
  FILE *f;
  struct FILECACHE *fc, **fcp;

/*************
printf (">> flopen: (%s, %s)\n", file_name, open_mode);
fflush (stdout);
*************/

  for (fcp= &filecache;
       (fc= *fcp) != (struct FILECACHE *) 0;
       fcp= &(*fcp)->next)
  {
    if (strcmp (fc->name, file_name) == 0)
    {
      if (strcmp (fc->mode, open_mode) == 0) return (fc->fp);

/*********
printf (">>> fclose: (%s), was %s\n", file_name, fc->mode);
********/
      fclose (fc->fp);
      *fcp= fc->next;
      free (fc);
      break;
    }
  }

  if (strcmp (open_mode, "close") == 0) return (FILE *) 0;

/**********
printf (">>> fopen: (%s, %s)\n", file_name, open_mode);
********/
  if ((f= fopen (file_name, open_mode)) == (FILE *) 0)
  {
    /***********
    fprintf (stderr, "flopen (%s, %s) failed!\n", file_name, open_mode);
    ***********/
    return (FILE *) 0;
  }

  if ((fc= (struct FILECACHE *)
           calloc (sizeof (struct FILECACHE) + strlen (file_name), 1))
      == (struct FILECACHE *) 0) return f;

  fc->fp= f;
  strcpy (fc->mode, open_mode);
  strcpy (fc->name, file_name);
  fc->next= filecache;
  filecache= fc;

  return f;
}

/* ------------------------------------------------------------------------ */
int flclose (char *file_name)
{
  flopen (file_name, "close");
  return 0;
}

/* ------------------------------------------------------------------------ */
int flclose_all ()
{
  struct FILECACHE *fc;

/**************
printf (">> flclose_all: ()\n");
************/
  while (filecache != (struct FILECACHE *) 0)
  {
    fc= filecache;
    filecache= filecache->next;
    fclose (fc->fp);
    free (fc);
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
int flprint_table (FILE *fo)
{
  struct FILECACHE *fc;

  fprintf (fo, "lazy file table (BEGIN)\n");
  for (fc= filecache; fc != (struct FILECACHE *) 0; fc= fc->next)
    fprintf (fo, "0x%08lX %3s %s\n", (long) fc->fp, fc->mode, fc->name);

  fprintf (fo, "lazy file table (END)\n");

  return 0;
}

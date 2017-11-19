/*
 *  FILE %sbr/fnmqueue.c
 *
 *  *** OBSOLETE ***
 *
 *  Verwaltung einer Liste von Strings mit den Operationen
 *  o  queue    ... einfÅgen hinten
 *  o  push     ... einfÅgen vorne
 *  o  pull     ... entnehmen vorne
 *
 *  written:       1991-03-15
 *  latest update: 1996-05-06 10:43:17
 *
 */

*** OBSOLETE ***

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
struct FILENAMES
{
  struct FILENAMES *next;
  char *fnm;
} ;

/* ------------------------------------------------------------------------ */
static struct FILENAMES *filenames= (struct FILENAMES *) 0;
static struct FILENAMES **fnmapp= &filenames;

/* ------------------------------------------------------------------------ */
int string_queue (char *fn)
{
  struct FILENAMES *f;

  f= (struct FILENAMES *) malloc (sizeof (struct FILENAMES));
  if (f == (struct FILENAMES *) 0) return -1;

  f->fnm= strdup (fn);
  f->next= (struct FILENAMES *) 0;
  *fnmapp= f;
   fnmapp= &f->next;

  return 0;
}

/* ------------------------------------------------------------------------ */
int string_push (char *fn)
{
  struct FILENAMES *f;

  f= (struct FILENAMES *)malloc (sizeof (struct FILENAMES));
  if (f == (struct FILENAMES *) 0) return -1;

  f->fnm= strdup (fn);
  f->next= filenames;
  if (fnmapp == &filenames) /* Liste war bisher leer */
  {
    fnmapp= &f->next;
  }
  filenames= f;

  return 0;
}

/* ------------------------------------------------------------------------ */
char *string_pull ()
{
  struct FILENAMES *f;
  char *cp;

  if (filenames == (struct FILENAMES *) 0) return (char *) 0;
  cp= filenames->fnm;

  if (&filenames->next == fnmapp)
  {
    free (filenames);
    fnmapp= &filenames;
    filenames= (struct FILENAMES *) 0;
  }
  else
  {
    f= filenames;
    filenames= filenames->next;
    free (f);
  }

  return cp;
}

/* ------------------------------------------------------------------------ */
void string_reset ()
{
  struct FILENAMES *f;

  while ((f= filenames) != (struct FILENAMES *) 0)
  {
    f=f->next;
    free (filenames->fnm);
    free (filenames);
    filenames= f;
  }
}

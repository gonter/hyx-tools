/*
 *  FILE %sbr/fnames2.c
 *
 *  Suchen von Files ueber DOS
 *  Etwas hoehere Funktionen
 *
 *  written:       1989 04 12
 *                 1989 12 24: Fname_find () liefert ganzen Path des
 *                             gefundenen Files
 *                 1990 02 03: Revision
 *  latest update: 1996-08-11 10:42:29
 *
 */

#include <stdio.h>

#include <dos.h>
#include <string.h>
#include <gg/fnames.h>
#include <gg/filename.h>

static struct dta_buff dta;
static char last_path  [66];
static char found_file [66];
static char *found_file_ptr;
static int last_attr= -1;
static int init= -1;

/* ------------------------------------------------------------------------ */
struct dta_buff *Fdta_find (char *path, int attr)
{
  int notfound;
  int i;

  Fsetdta (&dta);
  if (init == -1) 
  {
    init= 0;
    goto FIRST;
  }

  if (strcmp (last_path, path) == 0 && last_attr == attr)
  { /* schon einmal nach diesem Muster gesucht */
    notfound= Fsnext ();
  }
  else
  { /* zum erstenmal nach diesem Muster UND Attribut gesucht */
FIRST:
    last_attr= attr;
    strcpy (last_path,  path);
    strcpy (found_file, path);
    notfound= Fsfirst (path, attr);

    for (i= strlen (path)-1; i >= 0; i--)
      if (path [i] == '\\' || path [i] == ':') break;

    found_file_ptr= (i >= 0) ? &found_file [i+1] : found_file;
  }

  if (notfound)
  {
    return (struct dta_buff *) 0;
  }
  else
  {
    if (dta.att & FA_DIRECTORY) dta.size= 0L;
    return &dta;
  }
}

/* ------------------------------------------------------------------------ */
char *Fname_find (char *path, int attr)
{
  if (Fdta_find (path, attr) == (struct dta_buff *) 0)
    return (char *) 0;

  strcpy (found_file_ptr, dta.name);
  return found_file;  
}

/* ------------------------------------------------------------------------ */
struct dta_buff *Fget_dta (void)
{
  return &dta;
}

/* ------------------------------------------------------------------------ */
void Freset_find (void)
{
  init= -1;
}

/* ------------------------------------------------------------------------ */
int wcrd_get_date () { return dta.date; }
int wcrd_get_time () { return dta.time; }
long wcrd_get_size () { return dta.size; }

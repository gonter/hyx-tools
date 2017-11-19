/*
 *  FILE %sbr/wcrd_d01.c
 *
 *  redesigned wildcard matching
 *  MSDOS version
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1996-08-11 10:43:26
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/fnames.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_rec_wildcards (struct WCRD *wcrd, int lev)
{
  struct dta_buff l_dta;
  int actual_path_length;
  int look;
  int rc= 0;
  char *actual_filenm;
  char *actual_path;
  char *actual_pattern;

  actual_filenm=  wcrd->actual_filenm;
  actual_path=    wcrd->actual_path;
  actual_pattern= wcrd->actual_pattern;

  wcrd->current_level= lev;
  /* Fsetdta (&l_dta); */

#ifdef __wcrd_debug__
printf ("rec_wildcard: lev=%D actual_path=%s\n", lev, actual_path);
#endif

  actual_path_length= strlen (actual_path);
  if (actual_path_length)
       sprintf (actual_filenm, "%s\\%s", actual_path, actual_pattern);
  else sprintf (actual_filenm,     "%s",              actual_pattern);

#ifdef __wcrd_debug__
printf ("  actual_filenm=%s\n", actual_filenm);
#endif

  rc= wcrd2_wildcards (wcrd, actual_filenm);
  if (wcrd->leave > 0)
  {
    wcrd->leave--;
    return rc;
  }

  if (actual_path_length)
       sprintf (actual_filenm, "%s\\*.*", actual_path);
  else strcpy  (actual_filenm, "*.*");

  Fsetdta (&l_dta);
  for (look= Fsfirst (actual_filenm, FA_DIRECTORY);  /* search DIRS */
       !look;
       look= Fsnext ())
  {
    if ((l_dta.att & 0x10) == 0 ||
        strcmp (l_dta.name, ".")  == 0 ||
        strcmp (l_dta.name, "..") == 0)
       continue;

    if (actual_path_length)
         sprintf (actual_path + actual_path_length, "\\%s", l_dta.name);
    else sprintf (actual_path + actual_path_length,   "%s", l_dta.name);

#ifdef __wcrd_debug__
    printf ("rec_wildcards: pre  actual_path='%s'\n", actual_path);
#endif

    rc= wcrd2_rec_wildcards (wcrd, lev+1);

#ifdef __wcrd_debug__
    printf ("rec_wildcards: post actual_path='%s'\n", actual_path);
#endif

    if (wcrd->leave > 0)
    {
      wcrd->leave--;
      return rc;
    }

    Fsetdta (&l_dta);
  }

  return rc;
}

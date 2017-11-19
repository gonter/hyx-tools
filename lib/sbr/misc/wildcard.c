/*
 *  FILE %sbr/wildcard.c
 *
 *  MSDOS: wildcard matching ev. with recursion through subdirs
 *
 *                 1992 02 21: extracted from /usr/inc/temp.c
 *  latest update: 1998-07-19 11:17:17
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/fnames.h>
#include <gg/filename.h>

/* Where to search: recursion through directory tree: --------------------- */
static char actual_filenm  [128];       /* T2D: UNIX -> BUFFER OVERFLOW     */
static char actual_drive   [  2];
static char actual_path    [128];
static char actual_pattern [ 30];

static int  leave= 0;                   /* number of recursion levels       */
                                        /* to leave                         */
static int  subdirs= 0;                 /* 1 -> follow subdirectories       */
static int  match_mode= 0;              /* 0 -> use MSDOS's matching mode   */
                                        /* 1 -> use or own matchin mode     */
static int current_level;

/* ------------------------------------------------------------------------ */
static int cdecl rec_wildcards (int lev);

/* ------------------------------------------------------------------------ */
static int rec_wildcards (int lev)
{
  struct dta_buff l_dta;
  int actual_path_length;
  int look;
  int rc= 0;

  current_level= lev;
  Fsetdta (&l_dta);

/* fprintf (stderr, "%2d RC1: actual_path=%s\n", lev, actual_path); */
  actual_path_length = strlen (actual_path);
  if (actual_path_length)
       sprintf (actual_filenm, "%s\\%s", actual_path, actual_pattern);
  else sprintf (actual_filenm,     "%s",              actual_pattern);

  rc= wcrd_wildcards (actual_filenm);
  if (leave > 0)
  {
    leave--;
    return rc;
  }

  if (actual_path_length)
       sprintf (actual_filenm, "%s\\*.*", actual_path);
  else strcpy  (actual_filenm, "*.*");

  Fsetdta (&l_dta);
  for (look= Fsfirst (actual_filenm, 0x10);
       !look;
       look= Fsnext ())
  {
    if ((l_dta.att & 0x10) == 0 ||
        strcmp (l_dta.name, ".")  == 0 ||
        strcmp (l_dta.name, "..") == 0)
       continue;
    if (actual_path_length)
         sprintf (& actual_path [actual_path_length], "\\%s", l_dta.name);
    else sprintf (& actual_path [actual_path_length],   "%s", l_dta.name);
    rc= rec_wildcards (lev+1);
    if (leave > 0)
    {
      leave--;
      return rc;
    }
    Fsetdta (&l_dta);
  }

  return rc;
}

/* ------------------------------------------------------------------------ */
int wcrd_wildcards_or_rec (char *fn)
{
  int i;
  int drive_letter;
  int path_length;
  int rc= 0;

  leave= 0;

  if (subdirs)
  {
    for (i= strlen (fn) -1; i >= 0; i--)
      if (fn [i] == '\\' || fn [i] == ':') break;
    strcpy (actual_path, fn);

    if (i>=0)
         if (actual_path [i] == ':')
              actual_path [i+1]= 0;
         else actual_path [i  ]= 0;
    else      actual_path [  0]= 0;

    strcpy (actual_pattern, &fn [i+1]);
    if (actual_pattern [0] == 0)
       strcpy (actual_pattern, "*.*");
    path_length= strlen (actual_path);

    if (actual_path [1] == ':' && actual_path [0] == '*')
    {
      i= get_current_disk ();   /* aktuelles Drive ermitteln */
      drive_letter= select_disk (i);
      drive_letter += 'A';
      i &= 0x00FF;

      for (i= (i >= 2) ? 'C' : i+'A' ;
           i < drive_letter;
           i++)
      {
        actual_path [0]= (char) i;
        rc= rec_wildcards (1);
        if (leave > 0)
        {
          leave--;
          return rc;
        }
        actual_path [path_length]= 0;
      }
    }
    else
    {
      rc= rec_wildcards (1);
      if (leave > 0)
      {
        leave--;
        return rc;
      }
    }
  }
  else
  {
    path_length= strlen (fn);
    if (fn [1] == ':' && fn [0] == '*')
    {
      i= get_current_disk ();   /* aktuelles Drive ermitteln */
      drive_letter= select_disk (i);
      drive_letter += 'A';
      i &= 0x00FF;

      for (i= (i >= 2) ? 'C' : i+'A' ;
           i < drive_letter;
           i++)
      {
        fn [0]= (char) i;
        rc= wcrd_wildcards (fn);
        if (leave > 0)
        {
          leave--;
          return rc;
        }
        fn [path_length]= 0;
      }
    }
    else
    {
      rc= wcrd_wildcards (fn);
      if (leave > 0)
      {
        leave--;
        return rc;
      }
    }
  }

  return rc;
}

/* ------------------------------------------------------------------------ */
int wcrd_wildcards (char *fn)
{
  char *nm;
  int wild= 0;
  int rc= 0;

  wild= wcrd_wild_check (fn);

  if (wild)
  {
    if (match_mode)
    {
      to_upper (fn);
      while ((nm= Fname_find ("*.*", FA_FILE)) != (char *) 0)
        if (match (fn, nm) > 0)
        {
          if ((rc= main_fnc (nm)) < 0 || leave > 0) break;
        }
    }
    else
    {
      while ((nm= Fname_find (fn, FA_FILE)) != (char *) 0)
        if ((rc= main_fnc (nm)) < 0 || leave > 0) break;
    }
  }
  else rc= main_fnc (fn);

  return rc;
}

/* ------------------------------------------------------------------------ */
int wcrd_set_match_mode (int mode)
{
  match_mode= mode;

  return 0;
}

/* ------------------------------------------------------------------------ */
int wcrd_get_match_mode ()
{
  return match_mode;
}

/* ------------------------------------------------------------------------ */
int wcrd_set_subdirs (int mode)
{
  subdirs= mode;

  return 0;
}

/* ------------------------------------------------------------------------ */
int wcrd_get_subdirs ()
{
  return subdirs;
}

/* ------------------------------------------------------------------------ */
int wcrd_get_current_level ()
{
  return current_level;
}

/* ------------------------------------------------------------------------ */
int wcrd_leave (int levels)
{
  leave= (levels < 0) ? 999 : levels;

  return levels;
}

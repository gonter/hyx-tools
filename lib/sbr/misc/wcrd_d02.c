/*
 *  FILE %sbr/wcrd_d02.c
 *
 *  redesigned wildcard matching
 *  MSDOS version
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1996-08-11 10:43:53
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/fnames.h>
#include <gg/filename.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_wildcards_or_rec (struct WCRD *wcrd, char *fn)
{
  int i;
  int drive_letter;
  int path_length;
  int rc= 0;
  char *actual_path;
  char *actual_pattern;

  actual_path=    wcrd->actual_path;
  actual_pattern= wcrd->actual_pattern;

  wcrd->leave= 0;

#ifdef __wcrd_debug__
  printf ("wildcards_or_rec: fn='%s'\n", fn);
#endif

  if (wcrd->subdirs)
  {
    for (i= strlen (fn) -1; i >= 0; i--)
      if (fn [i] == '\\' || fn [i] == ':') break;
    strcpy (wcrd->actual_path, fn);
#ifdef __wcrd_debug__
    printf ("  actual_path= '%s'\n", actual_path);
#endif

    if (i >= 0)
         if (actual_path [i] == ':')
              actual_path [i+1]= 0;
         else actual_path [i  ]= 0;
    else      actual_path [  0]= 0;

#ifdef __wcrd_debug__
    printf ("  actual_path= '%s'\n", actual_path);
#endif

    strcpy (actual_pattern, &fn [i+1]);
    if (actual_pattern [0] == 0)
       strcpy (actual_pattern, "*.*");
    path_length= strlen (actual_path);

#ifdef __wcrd_debug__
    printf ("  actual_path= '%s'\n", actual_path);
#endif

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
        rc= wcrd2_rec_wildcards (wcrd, 1);
        if (wcrd->leave > 0)
        {
          wcrd->leave--;
          return rc;
        }
        actual_path [path_length]= 0;
      }
    }
    else
    {
#ifdef __wcrd_debug__
      printf ("  rec; actual_path= '%s'\n", actual_path);
#endif

      rc= wcrd2_rec_wildcards (wcrd, 1);
      if (wcrd->leave > 0)
      {
        wcrd->leave--;
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
        rc= wcrd2_wildcards (wcrd, fn);
        if (wcrd->leave > 0)
        {
          wcrd->leave--;
          return rc;
        }
        fn [path_length]= 0;
      }
    }
    else
    {
      rc= wcrd2_wildcards (wcrd, fn);
      if (wcrd->leave > 0)
      {
        wcrd->leave--;
        return rc;
      }
    }
  }

  return rc;
}

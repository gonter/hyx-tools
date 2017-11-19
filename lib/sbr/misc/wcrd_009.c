/*
 *  FILE %sbr/wcrd_009.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1997-03-23
 *  latest update: 1998-02-28  9:33:41
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/array.h>
#include <gg/filename.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_arguments (struct WCRD *wcrd, struct ARRAY_CONTROL *arguments)
{
  char *filenm= (char *) 0;
  int rc= 0;
  char *arg;
  FILE *fi2;

  if (wcrd == (struct WCRD *) 0
      || arguments == (struct ARRAY_CONTROL *) 0
     )
    return -1;

  if (array_elements (arguments) == 0) return 0;

  while ((arg= (char *) array_shift (arguments)) != (char *) 0)
  {
    if (arg [0] == '-')
    {
      if ((fi2= fopen (arg+2, "rt")) == (FILE *) 0)
      {
        fprintf (stderr, "File %s could not be read!\n", arg+2);
        rc= -1;
        break;
      }

      if (filenm == (char *) 0
          && (filenm= malloc (MAX_FNM_LENGTH)) == (char *) 0
         )
      {
        rc= -1;
        break;
      }

      for (;;)
      {
        rc= fread_line (fi2, filenm, MAX_FNM_LENGTH);
        if (rc <= 0 && feof (fi2)) break;
        if (wcrd2_wildcards (wcrd, filenm) == -1)
        {
          fclose (fi2);
          rc= -1;
          goto STOP;
        }
      }
      fclose (fi2);
    }
    else
    {
      if (wcrd2_wildcards (wcrd, arg) == -1)
      {
        rc= -1;
        goto STOP;
      }
    }
  }

STOP:
  free_or_what (filenm);

  return rc;
}

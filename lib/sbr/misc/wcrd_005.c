/*
 *  FILE %sbr/wcrd_005.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1996-08-10 12:43:48
 *
 */

#include <stdlib.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_dispose (struct WCRD *wcrd)
{
  if (wcrd == (struct WCRD *) 0) return -1;

  free (wcrd);

  return 0;
}

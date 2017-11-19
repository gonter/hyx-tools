/*
 *  FILE %sbr/wcrd_003.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1996-09-22 23:48:43
 *
 */

#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_leave (struct WCRD *wcrd, int levels)
{
  if (wcrd == (struct WCRD *) 0) return -1;

  wcrd->leave= (levels < 0) ? 999 : levels;

  return levels;
}

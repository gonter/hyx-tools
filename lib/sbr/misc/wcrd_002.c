/*
 *  FILE %sbr/wcrd_002.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1998-02-21  9:07:23
 *
 */

#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_set_subdirs (struct WCRD *wcrd, int mode)
{
  wcrd->subdirs= mode;

  return 0;
}

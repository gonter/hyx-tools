/*
 *  FILE %sbr/wcrd_004.c
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
struct WCRD *wcrd2_initialize ()
{
  struct WCRD *wcrd;

  wcrd= (struct WCRD *) calloc (sizeof (struct WCRD), 1);

  return wcrd;
}

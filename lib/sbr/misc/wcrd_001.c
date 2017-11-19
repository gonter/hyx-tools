/*
 *  FILE %sbr/wcrd_001.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1996-08-10 12:43:48
 *
 */

#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_set_match_mode (struct WCRD *wcrd, int mode)
{
  wcrd->match_mode= mode;

  return 0;
}

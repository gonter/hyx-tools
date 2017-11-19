/*
 *  FILE %sbr/wcrd_006.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1997-08-04 12:40:10
 *
 */

#include <stdlib.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_set_processor (
struct WCRD *wcrd,
int what,
WCRD_processor *prc,
void *client_data)
{
  if (wcrd == (struct WCRD *) 0) return -1;

  switch (what)
  {
    case WCRD_set_file_processor:
      wcrd->file_processor= prc;
      wcrd->file_client_data= client_data;
      break;

    case WCRD_set_dir_pre_processor:
      wcrd->dir_pre_processor= prc;
      wcrd->dir_pre_client_data= client_data;
      break;

    case WCRD_set_dir_post_processor:
      wcrd->dir_post_processor= prc;
      wcrd->dir_post_client_data= client_data;
      break;

    return -1;
  }

  return 0;
}

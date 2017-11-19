/*
 *  FILE %sbr/wcrd_007.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1998-02-21  9:01:53
 *
 */

#ifdef __wcrd_debug__
#include <stdio.h>
#endif
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_wildcards (struct WCRD *wcrd, char *fn)
{
  int wild= 0;
  int rc= 0;

  wild= wcrd_wild_check (fn);

#ifdef __wcrd_debug__
  printf ("wildcards: fn='%s' wild=%d\n", fn, wild);
#endif

  if (wild)
  {
    int separator;

#ifdef MSDOS
    to_upper (fn);
#endif /* MSDOS */

    separator= isolate_path (fn);
#ifdef __wcrd_debug__
    printf ("  separator=%d pattern='%s'\n", separator, fn+separator+1);
#endif

    if (separator > 0)
    {
      strncpy (wcrd->actual_path, fn, separator);
      wcrd->actual_path [separator]= 0;
    }
    else
    {
      wcrd->actual_path [0]= 0;
    }

    strcpy (wcrd->actual_pattern, fn+separator+1);
    wcrd->actual_index= separator;

    wcrd2_wildcards_search (wcrd);
  }
  else
  {
    WCRD_processor *prc;

    if ((prc= wcrd->file_processor) != (WCRD_processor *) 0)
      rc= (*prc) (fn, wcrd->file_client_data);
  }

  return rc;
}

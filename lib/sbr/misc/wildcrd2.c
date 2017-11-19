/*
 *  FILE %sbr/wildcrd2.c
 *
 *  written:       1995-02-12: extracted from /usr/utl/mv2.c
 *  latest update: 1996-08-10 13:02:29
 *
 */

#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int wcrd_wild_check (char *nm)
{
  for (; *nm; nm++)
    if (*nm == '*' || *nm == '?') return 1;

  return 0;
}

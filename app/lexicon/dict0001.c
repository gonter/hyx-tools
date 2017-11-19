/*
 *  FILE gg/app/lexicon/dict001.c
 *
 *  written:       1994-07-24
 *  latest update: 1999-11-28 13:08:31
 *
 */

#include <string.h>
#include <gg/filename.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
char *get_divided_lexicon (
char *base_name,
int divide_mode,
char *entry_key)
{
  int i;
  int m;
  char xfnm [24];

  switch (divide_mode)
  {
    case DAMODE_DIVIDE1: m= 6; break;
    case DAMODE_DIVIDE2: m= 7; break;
    case DAMODE_DIVIDE3: m= 8; break;
    default: return base_name;
  }

  for (i= 0; i < 5; i++) xfnm [i]= base_name [i];
  for (    ; i < m; i++) xfnm [i]= *entry_key++;
  for (    ; i < 8; i++) xfnm [i]= 'x';
  return fnmcpy2 (xfnm+i, ".hyx");
}

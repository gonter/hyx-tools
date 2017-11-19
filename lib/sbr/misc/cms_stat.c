/*
 *  FILE /usr/sbr/cms_stat.c
 * 
 *  simulate stat() for CMS
 *  >> Don't use it on a MSDOS or Unix machine  <<
 *  >> this function is simply pervert...       <<
 *
 *  1992 02 11
 *
 */

#include <stdio.h>
#include "ggcms.h"

/* ------------------------------------------------------------------------ */
int stat (char *fn, struct stat *st)
{
  FILE *f;

  f=fopen (fn, "rb");
  if (f == (FILE *) 0) return -1;
  fseek (f, 0L, 2);
  st->st_size = ftell (f);
  fclose (f);

  return 0;
}

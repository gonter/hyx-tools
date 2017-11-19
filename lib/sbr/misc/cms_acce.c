/*
 *  FILE /usr/sbr/cms_acce.c
 * 
 *  simulate access() for CMS
 *  >> Don't use it on a MSDOS or Unix machine  <<
 *  >> this function is simply pervert...       <<
 *
 *  1992 02 12
 *
 */

#include <stdio.h>
#include "ggcms.h"

/* ------------------------------------------------------------------------ */
int access (char *fn, int mode)
{
  FILE *f;

  f=fopen (fn, "rb");
  if (f == (FILE *) 0) return -1;
  fclose (f);

  return 0;
}

/*
 *  FILE %sbr/settmpfn.c
 *
 *  set a filename pointing into the /tmp directory
 *
 *  written:       1991 09 18
 *                 1991 12 13: moved to /usr/sbr
 *                             (before: /usr/ned/12/ned1202.c)
 *  latest update: 1999-04-25 17:00:55
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>

static int temp_counter= 1;

/* ------------------------------------------------------------------------ */
char *set_tmp_filename (char *dst, char *fnm)
{
  char *tmp;
  int fnm_allocated= 0;
  int tmp_lng;

  temp_counter++;
  tmp= getenv ("TMP");
  if (tmp == (char *) 0) tmp= "";
  if (fnm == (char *) 0)
  {
    fnm= malloc (16);
    sprintf (fnm, "@@@%05d.tmp", temp_counter);
    fnm_allocated= 1;
  }

  tmp_lng= strlen (tmp);
  if (dst == (char *) 0) dst= malloc (tmp_lng + strlen (fnm) + 2);
  if (dst == (char *) 0) return (char *) 0;
  strcpy (dst, tmp);
  if (tmp_lng > 0 && dst [tmp_lng-1] != '\\' && dst [tmp_lng-1] != '/')
    strcat (dst, "\\");
  strcat (dst, fnm);

  if (fnm_allocated) free (fnm);

  return dst;
}

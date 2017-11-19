/*
 *  FILE %ds/hytxt/hytxt014.c
 *
 *  written:       1991 07 20
 *                 1995-12-30
 *  latest update: 2001-02-18 19:10:33 (y2k bug)
 *  $Id: hytxt014.c,v 1.3 2003/09/30 09:57:33 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_write_stamp (FILE *fo, char *sig)
{
  struct tm *tm_s;
  time_t tt;
  int rc;
  char *user;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  if ((user= getenv ("NAME")) == (char *) 0) user= "user@unknown";

  rc= fprintf (fo,
        "<hyx.stamp d=\"%04d-%02d-%02d\" t=\"%02d:%02d:%02d\" u=\"%s\"",
        tm_s->tm_year+1900, tm_s->tm_mon+1, tm_s->tm_mday,
        tm_s->tm_hour, tm_s->tm_min,   tm_s->tm_sec,   user);

  if (sig != (char *) 0)
  {
    fputc (' ', fo);
    fputs (sig, fo);
    rc += strlen (sig) + 1;
  }

  fputc ('>', fo);
  rc++;

  return (long) rc;
}

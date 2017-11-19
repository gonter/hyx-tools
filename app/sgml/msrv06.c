/*
 *  FILE .../app/sgml/msrv06.c
 *
 *  see also: Mail Server Authorization
 *
 *  written:       1994-07-03
 *  latest update: 1999-04-25 17:03:53
 *  $Id: msrv06.c,v 1.5 2006/04/09 08:10:24 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <contrib/md5gg.h>
#include "msrvh.h"

#ifndef MSDOS
#include <syslog.h>
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
int msrv_check_authorization (
FILE *f_transcript,
struct MSRV_defaults *msd,
char *auth)
{
  int rv= MRas_wrong;
  struct MSRV_authorization *msrv_auth;
  char *md5_string;
  char *fields[2];

  if ((md5_string= MD5check_string ((unsigned char *) auth))
      == (char *) 0) goto REPORT;

  for (msrv_auth= msd->MD_authorization;
       msrv_auth != (struct MSRV_authorization *) 0;
       msrv_auth= msrv_auth->MA_next)
  {
    if (strcmp (msrv_auth->MA_key, md5_string) == 0)
    {
      rv= MRas_ok;
      break;
    }
  }

  if (f_transcript != (FILE *) 0)
  {
    fprintf (f_transcript,
             (rv != MRas_ok)
               ? "ATTENTION: authorization %s not ok!!\n"
               : "authorization ok",
             auth);
  }

REPORT:
  isolate_words (auth, fields, 2);
#ifndef MSDOS
  syslog (LOG_INFO, "msrv [%d] authorization %s/%d\n",
    getpid(), fields[0], rv);
#endif

  return rv;
}

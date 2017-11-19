/*
 *  FILE ~/usr/sgml/msrv01.c
 *
 *  written:       1994-06-18
 *  latest update: 1995-06-25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <syslog.h>
#include <gg/strings.h>
#include "msrvh.h"
#ifndef MSDOS
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
static char line [LINE_SIZE];
static char cmdline [LINE_SIZE];

static char From        [FIELD_SIZE];
static char Reply_To    [FIELD_SIZE];
static char Date        [FIELD_SIZE];
static char Subject     [FIELD_SIZE];

static char tmp         [FIELD_SIZE];

static int alphabet [256];

static struct MSRV_request Mrq;

/* ------------------------------------------------------------------------ */
static char *MSRV_transcript= "/tmp/msrv01.tmp";
static char *MCMD_retrieve= "retrieve";
static char *MCMD_help= "help";
static char *MCMD_get= "get";

/* ------------------------------------------------------------------------ */
static int reset_fields (void);
static int send_transcript (int transcript_status,
  struct MSRV_defaults *msrv_def, struct MSRV_request *mrq);

/* ------------------------------------------------------------------------ */
int msrv_process_requests (
FILE *fi,
struct MSRV_defaults *msrv_def)
{
  FILE *f_transcript= (FILE *) 0;
  int transcript_ok= 0;
  int rc;
  char *fields[2];
  char *kw;
  char *parm;
  char *repl_addr;
  int nfields;
  int i;
#define STAT_undef      0
#define STAT_header     1
#define STAT_body       2
  int stat= STAT_header;
  int auth_stat= MRas_anonymous;

  for (i= 0; i < 256; i++) alphabet [i]= 1;
  put_chartable (alphabet, " \t", 0);
  reset_fields ();

  Mrq.MR_From=        From;
  Mrq.MR_Subject=     Subject;
  Mrq.MR_Date=        Date;
  Mrq.MR_Reply_To=    Reply_To;
  Mrq.MR_authorization_status= auth_stat;

  for (;;)
  {
    rc= fread_line (fi, line, LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;

    if (strncmp (line, "From ", 5) == 0)
    {
      if (f_transcript != (FILE *) 0)
      {
        fclose (f_transcript);
        send_transcript (transcript_ok, msrv_def, &Mrq);
      }
      stat= STAT_header;
      reset_fields ();
      f_transcript= fopen (MSRV_transcript, "w");
      continue;
    }

    if (f_transcript != (FILE *) 0 && stat == STAT_body)
      fprintf (f_transcript, "> %s\n", line);

    nfields= isolate2words (line, fields, 2, alphabet);
    if (nfields > 2) nfields= 2;
    if (nfields == 0)
    {
      if ((repl_addr=
             msrv_pick_reply_address (Mrq.MR_From, Mrq.MR_Reply_To))
          == (char *) 0)
      {
        stat= STAT_undef;
        continue;
      }
      Mrq.MR_reply_address= repl_addr;
      printf ("repl_addr='%s'\n", repl_addr);
      if (f_transcript != (FILE *) 0)
      {
        msrv_prepare_reply_header (f_transcript, msrv_def, &Mrq);
        fprintf (f_transcript,
                 "Subject: Re: %s\n", Mrq.MR_Subject);
        fputc ('\n', f_transcript);
        fprintf (f_transcript, "TRANSCRIPT\n");
        transcript_ok= 1;
      }
      stat= STAT_body;
      continue;
    }

    kw= fields[0];
    Mrq.MR_action= kw;

    if (strcmp (kw, "reply") == 0
        || strcmp (kw, "transcript") == 0)
    { /* ignore anything else after that point */
      stat= STAT_undef;
      transcript_ok= 0;
      continue;
    }

    if (strcmp (kw, "quit") == 0
        || strcmp (kw, "bye") == 0
        || strcmp (kw, "thanks") == 0
        || strcmp (kw, "end") == 0)
    { /* ignore anything else after that point */
      stat= STAT_undef;
      if (f_transcript != (FILE *) 0)
      {
        fclose (f_transcript);
         if (transcript_ok)
        { /* ship the transcript */
          send_transcript (transcript_ok, msrv_def, &Mrq);
        }
        f_transcript= (FILE *) 0;
      }
      continue;
     }

    if (nfields == 1)
    {
      if (stat == STAT_body)
      {
        if (abbrev (MCMD_help, kw, 1) == 1)
        {
          Mrq.MR_action= MCMD_get;
          Mrq.MR_transformation= MRtr_simple;
          msrv_send_dbentry (f_transcript, msrv_def, &Mrq, "help");
        }
      }

      if (stat == STAT_body)
      {
        if (abbrev (MCMD_get, kw, 1) == 1)
          msrv_send_dbentry (f_transcript, msrv_def, &Mrq, "$$root");
      }
    } /* was: if (nfields == 1) */

    if (nfields == 2)
    {
      parm= fields[1];
      to_lower (kw);
      if (stat == STAT_header)
      {
        if (strcmp (kw, "from:") == 0) strcpy (From, parm);
        if (strcmp (kw, "date:") == 0) strcpy (Date, parm);
        if (strcmp (kw, "subject:") == 0) strcpy (Subject, parm);
        if (strcmp (kw, "reply-to:") == 0) strcpy (Reply_To, parm);
      }

      if (stat == STAT_body)
      {
        if (strcmp ("auth", kw) == 0)
        {
          auth_stat= msrv_check_authorization (f_transcript, msrv_def, parm);
          Mrq.MR_authorization_status= auth_stat;
        }

        if (abbrev (MCMD_get, kw, 1) == 1)
        {
          to_lower (parm);
          Mrq.MR_transformation= MRtr_simple;
          msrv_send_dbentry (f_transcript, msrv_def, &Mrq, parm);
        }

        if (abbrev (MCMD_retrieve, kw, 4) == 1)
        {
          Mrq.MR_transformation= MRtr_none;
          msrv_send_dbentry (f_transcript, msrv_def, &Mrq, parm);
        }

        if (abbrev ("help", kw, 1) == 1)
        {
          to_lower (parm);
          sprintf (tmp, "help %s", parm);
          Mrq.MR_action= MCMD_get;
          Mrq.MR_transformation= MRtr_simple;
          msrv_send_dbentry (f_transcript, msrv_def, &Mrq, tmp);
        }

      } /* was: if (stat == STAT_body) */
    } /* was: if (nfields == 2) */
  } /* was: for (;;) */

  return 0;
}

/* ------------------------------------------------------------------------ */
static int reset_fields ()
{
  From [0]= 0;
  Date [0]= 0;
  Reply_To [0]= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
static int send_transcript (
int transcript_ok,
struct MSRV_defaults *msrv_def,
struct MSRV_request *mrq)
{
#ifndef MSDOS
  int my_pid;

  my_pid= getpid();
  syslog (LOG_INFO, "msrv [%d] transcript to %s\n",
    getpid (), mrq->MR_reply_address);
#else
  mrq;
#endif

  if (transcript_ok)
    sprintf (cmdline, "/usr/lib/sendmail -t <%s", MSRV_transcript);
  else
    sprintf (cmdline, "/usr/lib/sendmail -bm %s <%s",
      msrv_def->MD_errors_to, MSRV_transcript);

  printf ("cmd=%s\n", cmdline);
  system (cmdline);

  return 0;
}

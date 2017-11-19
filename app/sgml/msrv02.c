/*
 *  FILE %sgml/msrv02.c
 *
 *  get a frame from the database and ship it
 *  -  t2d
 *
 *  written:       1994-06-19
 *  latest update: 1995-12-09
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/hyxd.h>
#include <gg/hytxt.h>
#include "msrvh.h"

#ifndef MSDOS
#include <syslog.h>
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
static char cmdline [LINE_SIZE];
static char *tmp_file1= "/tmp/msrv02a.tmp";
static char *tmp_file2= "/tmp/msrv02b.tmp";

/* ------------------------------------------------------------------------ */
int msrv_send_dbentry (
FILE *f_transcript,
struct MSRV_defaults *mdef,
struct MSRV_request *mrq,
char *frame_name)
{
  FILE *fo1;                    /* output for the complete returned mail    */
  FILE *fo2;                    /* temporary file for the extracted frame   */
  int retr_rc;                  /* return code from the retrieve operation  */
#ifndef MSDOS
  int my_pid;
#endif

#ifdef DIAGNOSTICS
  printf ("From:     %s\n", mrq->MR_From);
  printf ("Reply-To: %s\n", mrq->MR_Reply_To);
  printf ("Date:     %s\n", mrq->MR_Date);
  printf ("Database: %s\n", mdef->MD_database);
  printf ("Command:  %s %s\n", mrq->MR_action, frame_name);
#endif /* DIAGNOSTICS */

  /* prepare the header of the reply */
  if ((fo1= fopen (tmp_file1, "w")) == (FILE *) 0) return -1;
  msrv_prepare_reply_header (fo1, mdef, mrq);
  fprintf (fo1, "Subject: Re: %s %s\n", mrq->MR_action, frame_name);
  fputc ('\n', fo1);
  fprintf (fo1, "REPLY\n");

  /* fetch the requested frame */
  if (f_transcript != (FILE *) 0)
    fprintf (f_transcript, "database %s, retrieving frame '%s'\n",
             mdef->MD_database, frame_name);

  switch (mrq->MR_transformation)
  {
    case MRtr_simple:
      if ((fo2= fopen (tmp_file2, "w")) == (FILE *) 0) return -1;
      retr_rc= hyx_d_extract (fo2, mdef->MD_database, frame_name,
                             (char *) 0, 0x00);
      fclose (fo2);
      /* strip the frame and append it to the header file */
      if (retr_rc == 0)
      {
        if (f_transcript != (FILE *) 0)
          fprintf (f_transcript, "... stripping it\n");
        chksgml_file (fo1, stdout, tmp_file2, 0, 0L, 0x7FFFFFFFL, 0);
      }
      break;

    default:
      retr_rc= hyx_d_extract (fo1, mdef->MD_database, frame_name,
                             (char *) 0, 0x00);
      break;
  }

  if (retr_rc != 0)
  {
    if (f_transcript != (FILE *) 0)
      fprintf (f_transcript, "sorry, can't find frame '%s'\n", frame_name);
  }

  fclose (fo1);

#ifndef MSDOS
  my_pid= getpid();
  syslog (LOG_INFO, "msrv [%d] sending (%s) '%s'\n",
    getpid (), mdef->MD_database, frame_name);
  syslog (LOG_INFO, "msrv [%d] to %s\n", getpid (), mrq->MR_reply_address);
#endif

  sprintf (cmdline, "/usr/lib/sendmail -t <%s", tmp_file1);
  printf ("cmd=%s\n", cmdline);
  system (cmdline);

  return 0;
}

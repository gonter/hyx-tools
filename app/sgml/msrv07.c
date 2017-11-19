/*
 *  FILE ~/usr/gophtool/msrv02.c
 *
 *  write the header of a mail server reply
 *
 *  written:       1994-07-14
 *  latest update: 1994-07-14
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>
#include "msrvh.h"

/* ------------------------------------------------------------------------ */
int msrv_prepare_reply_header (
FILE *fo,
struct MSRV_defaults *mdef,
struct MSRV_request *mrq)
{
  fprintf (fo, "From: %s\n", mdef->MD_sender);
  fprintf (fo, "To: %s\n", mrq->MR_reply_address);
  if (mdef->MD_cc != (char *) 0)
    fprintf (fo, "Cc: %s\n", mdef->MD_cc);
  if (mdef->MD_errors_to != (char *) 0)
    fprintf (fo, "Errors-To: %s\n", mdef->MD_errors_to);
  if (mdef->MD_name != (char *) 0)
    fprintf (fo, "Comment: %s\n", mdef->MD_name);

  return 0;
}

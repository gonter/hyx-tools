/*
 *  FILE ~/usr/ned/04/ned0431.c
 *
 *  THIS MODULE IS NOT USED ANYWHERE
 *
 *  read file or frame from a dorothy server
 *
 *  written:       1993 01 18
 *  latest update: 1998-08-16 12:39:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

int kbin (void);

/* ------------------------------------------------------------------------ */
int dorothy_rw (
char *tmpfnm,
char *server,
long port,
char *action,
char *cl_or_file,
char *fr)
{
  char cmd_line [150];
  char rc_str [20];
  int rc;

  if (fr == (char *) 0) fr="";

  sprintf (cmd_line,
           "dorothy -h%s -p%ld %s %s %s %s",
                      server,
                           port,
                               action,
                                  tmpfnm,
                                     cl_or_file,
                                        fr);

  rc= system (cmd_line);
  sprintf (rc_str, "*KEY* %d: ", rc),
  ned_message_2 (rc_str, cmd_line);
kbin();

  return rc;
}

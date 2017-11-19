/*
 *  FILE ~/usr/sgml/hyxd05.c
 *
 *  Hypertext daemon
 *
 *  written:       1994-04-09
 *  latest update: 1995-07-02
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/hyxd.h>

#define LINE_SIZE 1024
static char line [LINE_SIZE];

/* ------------------------------------------------------------------------ */
int http4hyx_daemon (
FILE *fi,                               /* input stream         */
FILE *fo,                               /* output stream        */
int mode)
{
  int rc;

  for (;;)
  {
    rc= fread_line (fi, line, LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;
    if (line [0] == '#') continue;
    if (http4hyx_command (fo, line, mode) == 1) break;
  }

  return 0;
}

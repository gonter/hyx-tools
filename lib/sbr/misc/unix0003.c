/*
 *  FILE %sbr/unix0003.c
 *
 *  written:       1995-08-20
 *  latest update: 1995-08-20
 *
 */

#include <stdio.h>
#include <syslog.h>

/* ------------------------------------------------------------------------ */
int syslog (
int log_level,
char *s,
long p1,
long p2,
long p3,
long p4,
long p5,
long p6,
long p7,
long p8,
long p9)
{
  return fprintf (stderr, s, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

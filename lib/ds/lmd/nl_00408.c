/*
 *  FILE ~/usr/nl_kr/lib/nl_00408.c
 *
 *  data
 *  - functions to create LUTs -- using YTREE
 *  - see also: wordcr05.c (word reference system)
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *  latest update: 1994-12-19: isolated from wordcr04.c
 *  $Id: nl_00408.c,v 1.2 2001/02/06 20:06:33 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
void lmd_error04 (char *msg)
{
  printf ("ERROR: %s\n", msg);
}

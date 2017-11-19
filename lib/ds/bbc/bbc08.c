/*
 *  FILE %lexicon/bbc08.c
 *
 *  written:       1995-08-21
 *  latest update: 1995-08-21
 *  $Id: bbc08.c,v 1.3 2003/06/25 03:09:53 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_get_request (
struct BBC_CONNECTION *bbcc,
char *buffer)
{
#define N_FIELDS 10
  char *fields [N_FIELDS];
  int field_count;
  BBC_accept *accept_handler;

  if ((field_count= split_string (buffer, ':', fields, N_FIELDS)) < 3
      || strcmp (fields [0], "BBC") != 0
      || strcmp (fields [1], "REQUEST") != 0
     ) return -1;

  bbcc->BBCC_resource= strdup (fields [2]);

  if ((accept_handler= bbcc->BBCC_accept) == (BBC_accept *) 0
      || (*accept_handler) (bbcc) != 0
     ) return -1;

  return 0;
}

/*
 *  FILE %lexicon/bbc11.c
 *
 *  send a challenge to a bbc target
 *
 *  written:       1995-08-14
 *  latest update: 1995-08-17
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>
#include <gg/dpp.h>
#include <gg/bbch.h>

static char PUBLIC []= "PUBLIC";

/* ------------------------------------------------------------------------ */
int bbc_challenge (
struct BBC_SESSION *bbcs,
struct BBC_CONNECTION *bbcc,
char *buffer)
{
  char *chex_string;
#define N_FIELDS 10
  char *fields [N_FIELDS];
  char tmp_pass [20];
  int field_count;

  /* printf ("# key_file= '%s'\n", bbcs->BBCS_key_file); */

  if ((field_count= split_string (buffer, ':', fields, N_FIELDS)) < 4
     || strcmp (fields [0], "BBC") != 0
     || strcmp (fields [1], "ACCEPT") != 0) return -1;
     
  bbcc->BBCC_opening_challenge= strdup (fields [2]);
  bbcc->BBCC_s_p2o.GGC_challenge= strdup (fields [3]);
  bbcc->BBCC_s_o2p.GGC_challenge= "OPEN";

  if (strcmp (fields [2], PUBLIC) != 0)
  {
    if ((chex_string= agettok_get_challenge (bbcs->BBCS_key_file,
                   bbcc->BBCC_from, bbcc->BBCC_to, bbcc->BBCC_resource,
                   bbcc->BBCC_opening_challenge))
        == (char *) 0)
      return -1;

    if (!bbcs->BBCS_is_public)
    {
      mk_PassWord (tmp_pass, 16);
      bbcc->BBCC_s_o2p.GGC_challenge= strdup (tmp_pass);
    }
  }
  else
  {
    chex_string= fields [2];
  }

  bbcc->BBCC_chex_string= strdup (chex_string);

  return 0;
}

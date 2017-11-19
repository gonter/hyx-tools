/*
 *  FILE %ds/bbc/bbc05.c
 *
 *  written:       1995-08-04
 *  latest update: 1996-12-01 15:52:59
 *  $Id: bbc05.c,v 1.4 2003/06/25 10:11:44 gonter Exp $
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
#ifdef DIAGNOSTICS
#define STRCMP(s1,s2) _strcmp(s1,s2,__LINE__)
#endif

#ifdef STRCMP
static int _strcmp (char *s1, char *s2, int l)
{
  int rc;
  fprintf (stderr, "strcmp [%d]: s1='%s'\n", l, s1);
  fprintf (stderr, "strcmp [%d]: s2='%s'\n", l, s2);
  rc= strcmp (s1, s2);
  fprintf (stderr, "strcmp [%d]: rc='%d'\n", l, rc);
  return rc;
}
#else
#define STRCMP strcmp
#endif

/* ------------------------------------------------------------------------ */
int bbc_chex (
struct BBC_SESSION *bbcs,
struct BBC_CONNECTION *bbcc,
char *buffer)
{
  char *chex_string;
#define N_FIELDS 10
  char *fields [N_FIELDS];
  int field_count;

  fprintf (stderr, "# key_file= '%s'\n", bbcs->BBCS_key_file);
  fprintf (stderr, "buffer='%s'\n", buffer);

  if ((field_count= split_string (buffer, ':', fields, N_FIELDS)) < 7
      || STRCMP (fields [0], "BBC") != 0
      || STRCMP (fields [1], "CONNECT") != 0
     ) return -1;

  /** fprintf (stderr, "op_ch='%s'\n", bbcc->BBCC_opening_challenge); **/
  /* T2D */
  if (STRCMP (bbcc->BBCC_opening_challenge, PUBLIC) != 0)
  {
    chex_string= agettok_get_challenge (bbcs->BBCS_key_file,
                              fields [2], fields [3], fields [4],
                              bbcc->BBCC_opening_challenge);
    /*** fprintf (stderr, "chex_string='%s'\n", chex_string); ***/

    if (chex_string == (char *) 0
        || STRCMP (fields [5], chex_string) != 0
       ) return -1;
  }

  bbcc->BBCC_from=        strdup (fields [2]);
  bbcc->BBCC_to=          strdup (fields [3]);
  bbcc->BBCC_resource=    strdup (fields [4]);
  bbcc->BBCC_chex_string= strdup (fields [5]);

  bbcc->BBCC_s_p2o.GGC_challenge= strdup (fields [6]);

  /* set session key for communication from peer to this object */
  ggc_set_session_key (&bbcc->BBCC_s_p2o, bbcs->BBCS_key_file,
                       fields [2], fields [3], fields [4]);

  /* set session key for communication from this object to peer */
  ggc_set_session_key (&bbcc->BBCC_s_o2p, bbcs->BBCS_key_file,
                       fields [2], fields [3], fields [4]);


  return 0;
}

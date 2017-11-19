/*
 *  FILE %lexicon/bbc06.c
 *
 *  written:       1995-08-04
 *  latest update: 1995-08-17
 *  $Id: bbc06.c,v 1.2 2003/06/25 03:09:53 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/ggcrypt.h>
#include <gg/dpp.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_diag_conn_sess (FILE *fo, struct GG_CRYPT *ggc)
{
  char t [40];

  fprintf (fo, "challenge:      '%s'\n", ggc->GGC_challenge);

  if (ggc->GGC_key != (char *) 0)
  {
    fprintf (fo, "key_string:     '%s'\n", ggc->GGC_key_str);

    bin_to_hex (ggc->GGC_key, t, 16);
    fprintf (fo, "key_str (test): '%s'\n", t);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int bbc_diag_conn (FILE *fo, struct BBC_CONNECTION *bbcc)
{
  fprintf (fo, "from:        '%s'\n", bbcc->BBCC_from);
  fprintf (fo, "to:          '%s'\n", bbcc->BBCC_to);
  fprintf (fo, "resource:    '%s'\n", bbcc->BBCC_resource);
  fprintf (fo, "challenge:   '%s'\n", bbcc->BBCC_opening_challenge);
  fprintf (fo, "chex_string: '%s'\n", bbcc->BBCC_chex_string);

  fprintf (fo, "encryption object to peer:\n");
  bbc_diag_conn_sess (fo, &bbcc->BBCC_s_o2p);
  fprintf (fo, "encryption peer to object:\n");
  bbc_diag_conn_sess (fo, &bbcc->BBCC_s_p2o);

  return 0;
}

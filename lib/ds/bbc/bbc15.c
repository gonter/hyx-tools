/*
 *  FILE %ds/bbc/bbc15.c
 *
 *  written:       1995-08-21
 *  latest update: 1996-12-01 11:42:05
 *  $Id: bbc15.c,v 1.3 2003/06/25 03:09:53 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_acceptor (void *client_data)
{
  struct BBC_SESSION *bbcs;
  struct BBC_CONNECTION *bbcc;

  if ((bbcc= (struct BBC_CONNECTION *) client_data)
         == (struct BBC_CONNECTION *) 0
      || (bbcs= (struct BBC_SESSION *) bbcc->BBCC_bbcs)
         == (struct BBC_SESSION *) 0
      || bbcs->sig != SIG_BBC_SESSION
     ) return -1;

  if (bbcs->BBCS_is_public
      || (bbcs->BBCS_public_resource != (char *) 0
          && strcmp (bbcs->BBCS_public_resource, bbcc->BBCC_resource) == 0)
     )
  {
    bbcc->BBCC_opening_challenge= "PUBLIC";
    bbcc->BBCC_s_o2p.GGC_challenge= "OPEN";
    bbcc->BBCC_s_p2o.GGC_challenge= "OPEN";
  }

  return 0;
}

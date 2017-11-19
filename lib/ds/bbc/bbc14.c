/*
 *  FILE %ds/bbc/bbc14.c
 *
 *  written:       1995-08-21
 *  latest update: 1996-12-01 11:41:24
 *  $Id: bbc14.c,v 1.3 2003/06/25 10:11:44 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
struct BBC_SESSION *bbc_new_session ()
{
  struct BBC_SESSION *bbcs;

  if ((bbcs= (struct BBC_SESSION *) calloc (sizeof (struct BBC_SESSION), 1))
      != (struct BBC_SESSION *) 0)
  {
    bbcs->sig= SIG_BBC_SESSION;

    /* standard methods */
    bbcs->BBCS_accept= bbc_acceptor;
    bbcs->BBCS_input1= bbc_authentication_protocol;
    bbcs->BBCS_input2= bbc_to_stdout;
  }

  return bbcs;
}

/*
 *  FILE %ds/bbc/bbc03.c
 *
 *  Setup connection descriptor for an established connection.
 *  This function is used for incoming and outgoing connections.
 *
 *  written:       1995-08-03
 *  latest update: 1999-05-12 15:11:27
 *  $Id: bbc03.c,v 1.4 2003/06/25 03:09:53 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
struct BBC_CONNECTION *bbc_init_connection (
struct BBC_SESSION *bbcs,
int sock)
{
  struct BBC_CONNECTION *nbc;
  char peer_host [MAX_HN_LNG];
  char peer_ipnum [MAX_HN_LNG];

  if ((nbc= bbc_new_connection ()) == (struct BBC_CONNECTION *) 0)
    return (struct BBC_CONNECTION *) 0;

  inet_netnames (sock, peer_host, peer_ipnum);

  /* link new connection into session control and vica versa */
  nbc->BBCC_bbcs= (void *) bbcs;
  nbc->BBCC_next= bbcs->BBCS_connections;
  bbcs->BBCS_connections= nbc;

  nbc->BBCC_peer_host= strdup (peer_host);
  nbc->BBCC_peer_ipnum= strdup (peer_ipnum);

  nbc->BBCC_socket= sock;

  /* inheritance of various methods */
  nbc->BBCC_accept= bbcs->BBCS_accept;
  nbc->BBCC_input1= bbcs->BBCS_input1;
  nbc->BBCC_input2= bbcs->BBCS_input2;
  nbc->BBCC_client_data1= bbcs->BBCS_client_data1;
  nbc->BBCC_op= bbcs->BBCS_op;

  /* setup challenges just to be on the safe side */
  mk_PassWord (peer_host, 16);
  nbc->BBCC_opening_challenge= strdup (peer_host);
  mk_PassWord (peer_host, 16);
  nbc->BBCC_s_o2p.GGC_challenge= strdup (peer_host);
  mk_PassWord (peer_host, 16);
  nbc->BBCC_s_p2o.GGC_challenge= strdup (peer_host);

  return nbc;
}

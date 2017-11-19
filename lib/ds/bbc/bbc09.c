/*
 *  FILE %ds/bbc/bbc09.c
 *
 *  listen on a port
 *
 *  written:       1995-08-07
 *  latest update: 1999-05-09 18:08:38
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
struct BBC_LISTEN *bbc_server (int port)
{
  struct sockaddr_in sock_addr;
  struct BBC_LISTEN *bbcl;
  int sock_listen;
  int one= 1;
  int rc;

  if ((bbcl= (struct BBC_LISTEN *) calloc (sizeof (struct BBC_LISTEN), 1))
      == (struct BBC_LISTEN *) 0)
ERROR:
    return (struct BBC_LISTEN *) 0;
  
  /* set up listening socket */
  sock_listen= socket (AF_INET, SOCK_STREAM, 0);

  /* fprintf (stderr, "gethostid(): %ld\n", gethostid()); */
  sock_addr.sin_family= AF_INET;
  sock_addr.sin_addr.s_addr= htonl (INADDR_ANY);
  sock_addr.sin_port= 0;

  /* work as server and wait until someone else connects ... */
  fprintf (stderr, "listening on port %d\n", port);
  sock_addr.sin_port= htons (port);

  if (setsockopt (sock_listen, (int) SOL_SOCKET, (int) SO_REUSEADDR,
                   (char *) &one, sizeof (int)) == -1)
  {
    fprintf (stderr, "can't setsockopt for listen sockfd");
    goto ERROR;
  }
                               
  if ((rc= bind (sock_listen, (struct sockaddr *) &sock_addr,
                 sizeof (struct sockaddr))) == -1)
  {
    fprintf (stderr, "bind: rc=%d errno=%d\n", rc, errno);
    goto ERROR;
  }

  if ((rc= listen (sock_listen, 1)) == -1)
  {
    fprintf (stderr, "listen: rc=%d errno=%d\n", rc, errno);
    goto ERROR;
  }

  fprintf (stderr, "listen on port %d: rc=%d\n", port, rc);

  bbcl->BBCL_socket= sock_listen;

  return bbcl;
}

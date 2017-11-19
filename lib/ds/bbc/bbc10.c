/*
 *  FILE %ds/bbc/bbc10.c
 *
 *  listen on a port
 *
 *  written:       1995-08-07
 *  latest update: 1996-12-01 12:58:12
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gg/strings.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
struct BBC_CONNECTION *bbc_connect (
struct BBC_SESSION *bbcs,
char *host,
int port,
char *target_name,
char *target_resource)
{
  struct BBC_CONNECTION *bbcc= (struct BBC_CONNECTION *) 0;
  struct sockaddr_in sock_addr;
  struct sockaddr_in other;
  int one= 1;
  int sock;
  int rc;
  char *cp;

  if (host == (char *) 0 || *host == 0 || port < 0) goto END;

  sock= socket (AF_INET, SOCK_STREAM, 0);
  sock_addr.sin_family= AF_INET;
  sock_addr.sin_port= 0;
  
  other.sin_family= AF_INET;
  other.sin_port= htons (port);

  if (verify (host, "0123456789."))
  {
    u_long adr;
    struct hostent *hostentry;

    if ((hostentry= gethostbyname (host)) == (struct hostent *) 0) goto END;

    adr= ((struct in_addr *) hostentry->h_addr_list[0])->s_addr,
         other.sin_addr.s_addr= adr;
  }
  else
  {
    other.sin_addr.s_addr= inet_addr (host);
  }

  /* fprintf (stderr, "connect to %s(%d)\n", host, port); */
  if ((rc= connect (sock,
                    (struct sockaddr *) &other,
                    sizeof (struct sockaddr_in)))
      == -1)
  {
    fprintf (stderr, "connect: errno=%d\n", errno);
    goto END;
  }

  if ((bbcc= bbc_init_connection (bbcs, sock)) != (struct BBC_CONNECTION *) 0)
  {
    bbcc->BBCC_status= BBCCst_initiator;
    bbcc->BBCC_connection_mode= BBCCcm_initiator;

    bbcc->BBCC_from= bbcs->BBCS_my_name;
    bbcc->BBCC_to= target_name;
    bbcc->BBCC_resource= target_resource;

    cp= bbcs->BBCS_buffer;
    sprintf (cp, "BBC:REQUEST:%s:hi.\n", target_resource);
    write (bbcc->BBCC_socket, cp, strlen (cp));
  }

END:
  return bbcc;
}

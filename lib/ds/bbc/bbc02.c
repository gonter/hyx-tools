/*
 *  FILE %ds/bbc/bbc02.c
 *
 *  Code stolen from nntp by gopherd developers.....
 *
 *  written:       1995-08-03
 *  latest update: 1996-12-15 18:13:08
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
#include <arpa/inet.h>
#include <netdb.h>

/*
 *
 * inet_netnames -- return the network, subnet, and host names of
 * our peer process for the Internet domain.
 *
 *      Parameters:     "sock" is our socket
 *                      "host_name"
 *                      is filled in by this routine with the
 *                      corresponding ASCII names of our peer.
 *       
 *                      if there doesn't exist a hostname in DNS etal,
 *                      the IP# will be inserted for the host_name
 *
 *                      "ipnum" is filled in with the ascii IP#
 *      Returns:        Nothing.
 *      Side effects:   None.
 */

void inet_netnames (
int  sockfd,
char *host_name,
char *ipnum)
{
  struct sockaddr_in      sa;
  int                     length;
  struct hostent          *hp;

  length= sizeof(sa);
  getpeername (sockfd, (struct sockaddr *) &sa, &length);
  strcpy (ipnum,     inet_ntoa (sa.sin_addr));
  strcpy (host_name, ipnum);

  hp= gethostbyaddr ((char *) &sa.sin_addr,
                     sizeof (sa.sin_addr.s_addr), AF_INET);
     
  if (hp != NULL) (void) strcpy (host_name, hp->h_name);
}

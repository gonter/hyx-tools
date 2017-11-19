/*
 *  FILE %ds/bbc/bbc01.c
 *
 *  open a TCP connection and transfer data in both directions
 *
 *  externaly defined macros:
 *  -  DIAGNOSTICS      write transfer protocol to stderr
 *
 *  written:       1995-08-03
 *  latest update: 1999-11-28 10:03:00
 *  $Id: bbc01.c,v 1.9 2003/10/01 21:52:01 gonter Exp $
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#include <sys/types.h>
#ifdef _AIX32
#include <sys/select.h>         /* AIX 3 defines fd_set there,              */
                                /* AIX 4 defines fd_set in <sys/time.h> !   */
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <gg/ggcrypt.h>
#include <gg/dirty.h>
#include <gg/bbch.h>

/* #define DIAGNOSTICS */

static int shutdown_flag= 0;    /* 1 -> shutdown asap */

/* ------------------------------------------------------------------------ */
void bbc_sig_term (int sig)
{
  shutdown_flag= 1;
}

/* ------------------------------------------------------------------------ */
int bbc_main (                  /* main network event loop processor        */
struct BBC_SESSION *bbcs,       /* session descriptor                       */
char *server,                   /* host name to connect to or NIL, if srv.  */
int port,                       /* port to connect to or listen on          */
int proc_stdin,                 /* 1 -> stdin needs to be watched           */
char *target_name,              /* name of opposite object entity           */
char *target_resource)          /* name of opposite object resource         */
{                               /*                                          */
  int num_in_socks= 0;          /* number of currently established conns.   */
  int doit= 1;                  /* event loop keeps running                 */
  int rv= 0;                    /* return code of this function             */
  int rc;                       /* return code obtained by called functions */
  int primary_socket= -1;       /* peer socket, first on, if defined ...    */
                                /* ... peer socket receives data from stdin */
  char *buffer;                 /* buffer to keep incoming data             */
#ifdef _AIX42                   /* addr_len is int in FreeBSD, Linux        */
  size_t addr_len;              /* length of peer socket address record     */
#else
  int addr_len;                 /* length of peer socket address record     */
#endif
  struct sockaddr_in other;     /* peer socket address record from accept   */
  struct BBC_CONNECTION *bbcc;  /* examined peer connection                 */
  struct BBC_CONNECTION *prim;  /* primary peer connection                  */
  struct BBC_LISTEN *bbcl=      /* socket where server listens on, ...      */
    (struct BBC_LISTEN *) 0;    /* ... if operating as a server             */
  BBC_input *input_handler;     /* processor to hand incoming data over     */
  fd_set mask;                  /* currently returned fd mask   */
  fd_set mask_save;             /* save fd mask                 */

#ifdef DIAGNOSTICS
  fprintf (stderr, "bbc_main (): proc_stdin=%d\n", proc_stdin);
#endif

  if (bbcs == (struct BBC_SESSION *) 0) return -1;
  buffer= bbcs->BBCS_buffer;

  FD_ZERO (&mask_save);

  if (server == (char *) 0 || *server == 0)
  {
    if ((bbcl= bbc_server (port)) == (struct BBC_LISTEN *) 0) return -1;

printf ("socket: listen %d\n", bbcl->BBCL_socket);
    FD_SET (bbcl->BBCL_socket, &mask_save);
    num_in_socks++;
  }
  else
  {
    if ((bbcc= bbc_connect (bbcs, server, port, target_name, target_resource))
       == (struct BBC_CONNECTION *) 0) return -1;

printf ("socket: connect %d\n", bbcc->BBCC_socket);
    FD_SET (bbcc->BBCC_socket, &mask_save);
    num_in_socks++;
  }

  if (doit)
  {
    signal (SIGTERM, bbc_sig_term);
  }

  while (doit && !shutdown_flag)
  {
#ifdef DIAGNOSTICS
    fprintf (stderr, "bbc_main (): main loop 1\n");
#endif

    memcpy (&mask, &mask_save, sizeof (fd_set));
    rc= select (32, &mask, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0);

#ifdef DIAGNOSTICS
  fprintf (stderr, "bbc_main (): main loop 2; rc=%d\n", rc);
#endif

    if (bbcl != (struct BBC_LISTEN *) 0
        && FD_ISSET (bbcl->BBCL_socket, &mask)
       )
    { /* established server connections           */
      rc= accept (bbcl->BBCL_socket, (struct sockaddr *) &other, &addr_len);
      if (rc == -1)
      {
        fprintf (stderr, "accept: rc=%d errno=%d shutdown_flag=%d\n",
                 rc, errno, shutdown_flag);
      }
      else
      {
        if ((bbcc= bbc_init_connection (bbcs, rc))
           != (struct BBC_CONNECTION *) 0)
        {
          fprintf (stderr, "connection [%d] from %s (%s)\n",
                   num_in_socks++,
                   bbcc->BBCC_peer_host, bbcc->BBCC_peer_ipnum);

          printf ("socket: incoming %d; shutdown_flag=%d\n",
                  bbcc->BBCC_socket, shutdown_flag);

          FD_SET (bbcc->BBCC_socket, &mask_save);
          bbcc->BBCC_connection_mode= BBCCcm_called;

        }
      }
    }

    /* check established incoming connections */
    for (bbcc= bbcs->BBCS_connections;
         bbcc != (struct BBC_CONNECTION *) 0;
         bbcc= bbcc->BBCC_next)
    {
      int s;
      s= bbcc->BBCC_socket;
/** fprintf (stderr, "s='%d'\n", s);  **/
      if (s == -1)
      { /* T2D: removed dead connection */
        continue;
      }

      if (FD_ISSET (bbcc->BBCC_socket, &mask))
      {
        rc= read (bbcc->BBCC_socket, buffer, BBCS_BUFFER_SIZE);
/** fprintf (stderr, "s='%d' ISSET rc=%d\n", s, rc); **/

          if (rc > 0)
          {
            if ((input_handler= bbcc->BBCC_input1) != (BBC_input *) 0)
              (*input_handler) ((void *) bbcc, buffer, rc);

            switch (bbcc->BBCC_t2d)
            {
              case BBCCt2d_shutdown: rc= -1; break;
              case BBCCt2d_pushup:
                if (proc_stdin && primary_socket == -1)
                {
                  FD_SET (0, &mask_save);
                  primary_socket= bbcc->BBCC_socket;
                  prim= bbcc;
                }
                break;
            }
          }

          if (rc <= 0) /* rc == 0: EOF; rc == -1: ERROR */
          { /* *** T2D: close that connection */
            fprintf (stderr, "closing connection from %s (%s) [rc=%d]\n",
                     bbcc->BBCC_peer_host, bbcc->BBCC_peer_ipnum, rc);

            num_in_socks--;
            if (num_in_socks == 0) doit= 0;

            if (bbcc->BBCC_socket == primary_socket)
            { /* T2D: check if this makes sense */
              primary_socket= -1;
              prim= (struct BBC_CONNECTION *) 0;

              /* don't shut down server if client goes away, but the client */
              /* should shut down, if the server closes the connection.     */
              if (server != (char *) 0) doit= 0;
            }

            FD_CLR (bbcc->BBCC_socket, &mask_save);
            close (bbcc->BBCC_socket);
            bbcc->BBCC_socket= -1;
          }
      }
    }

    if (FD_ISSET (0, &mask))    /* pipe from stdin */
    {
      rc= read (0, buffer, BBCS_BUFFER_SIZE);
      if (rc <= 0) doit= 0;

#ifdef DIAGNOSTICS
      fprintf (stderr, "<<<< DIAG: %d bytes stdin to net\n", rc);
      dump (stderr, buffer, rc);
#endif

      if (primary_socket > -1)
      {
        ggc_block_cfb (&prim->BBCC_s_o2p, buffer, rc);
        write (primary_socket, buffer, rc);
      }
    }
  }

  printf ("bbc01: shutdown_flag=%d\n", shutdown_flag);
  if (bbcl != (struct BBC_LISTEN *) 0) close (bbcl->BBCL_socket);

  for (bbcc= bbcs->BBCS_connections;
       bbcc != (struct BBC_CONNECTION *) 0;
       bbcc= bbcc->BBCC_next)
  {
    if (bbcc->BBCC_socket >= 0)
    {
      close (bbcc->BBCC_socket);
      bbcc->BBCC_socket= -1;
    }
  }

  return rv;
}

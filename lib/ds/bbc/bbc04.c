/*
 *  FILE %ds/bbc/bbc04.c
 *
 *  BBC core authentication protocl
 *
 *  This is the main protocol engine for the target as
 *  well as the initiator that
 *  - takes care of the initial exchange of credentials
 *  - sets up the session keys
 *  - exchanges a block of random data
 *  - receives incoming data
 *
 *  written:       1995-08-03
 *  latest update: 1997-03-23 10:41:37
 *  $Id: bbc04.c,v 1.5 2003/10/01 21:52:01 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <gg/dirty.h>
#include <gg/ggcrypt.h>
#include <gg/bbch.h>
#include <gg/strings.h>

/* #define DEBUGG1 */

/* ------------------------------------------------------------------------ */
int bbc_authentication_protocol (
void *client_data,
char *buffer,
int buffer_size)
{
  struct BBC_CONNECTION *bbcc;  /* connection currently processed           */
  struct BBC_SESSION *bbcs;
  BBC_input *input_handler;
  int rc;
  char *cp;
  char *xmit_buffer;

  if ((bbcc= (struct BBC_CONNECTION *) client_data)
       == (struct BBC_CONNECTION *) 0
      || (bbcs= (struct BBC_SESSION *) bbcc->BBCC_bbcs)
        == (struct BBC_SESSION *) 0
     ) return -1;

  xmit_buffer= bbcs->BBCS_buffer;
  bbcc->BBCC_t2d= BBCCt2d_nothing;

#ifdef DEBUGG1
  fprintf (stderr, ">>>> DIAG: %d bytes from %s\n",
           buffer_size, bbcc->BBCC_peer_host);

  dump (stderr, buffer, (int) buffer_size);
  /* write (1, buffer, (int) buffer_size); */
#endif /* DEBUGG1 */

  switch (bbcc->BBCC_status)
  {
    case BBCCst_target:
      buffer [buffer_size]= 0;
#ifdef DEBUGG1
      fprintf (stderr, ">>> opening string: '%s'\n", buffer);
#endif /* DEBUGG1 */
      rc= bbc_get_request (bbcc, buffer);
#ifdef DEBUGG1
      fprintf (stderr, ">>> rc=%d\n", rc);
#endif /* DEBUGG1 */
      if (rc != 0) goto FAILED;

      sprintf (xmit_buffer,
               "BBC:ACCEPT:%s:%s:pleased to meet you, %.32s.\n",
               bbcc->BBCC_opening_challenge,
               bbcc->BBCC_s_o2p.GGC_challenge,
               bbcc->BBCC_peer_host);

      write (bbcc->BBCC_socket, xmit_buffer, strlen (xmit_buffer));
      bbcc->BBCC_status= BBCCst_target2;
      break;

    case BBCCst_target2:
      buffer [buffer_size]= 0;
#ifdef DEBUGG1
      fprintf (stderr, ">>> opening string: '%s'\n", buffer);
#endif /* DEBUGG1 */
      rc= bbc_chex (bbcs, bbcc, buffer);
#ifdef DEBUGG1
      fprintf (stderr, ">>> rc=%d\n", rc);
#endif /* DEBUGG1 */

      if (rc == 0)
      {
#ifdef DEBUGG1
        bbc_diag_conn (stdout, bbcc);
#endif /* DEBUGG1 */
        bbcc->BBCC_status= BBCCst_target_wait_random;
        cp= "BBC:OK:let's go...\n";
      }
      else
      {
FAILED:
        bbcc->BBCC_status= BBCCst_failed;
        bbcc->BBCC_t2d= BBCCt2d_shutdown;
        cp= "BBC:FAILED:sorry.\n";
      }
      write (bbcc->BBCC_socket, cp, strlen (cp));
      return 0;

    case BBCCst_target_wait_random:
      /* This is the target which receives a block of random data           */
      /* and answers with another block of random data.                     */
      /* After that, the communication channel is set up completely.        */

      ggc_block_cfb (&bbcc->BBCC_s_p2o, buffer, buffer_size);
      mk_PassWord (xmit_buffer, RANDOM_SIZE);
      xmit_buffer [RANDOM_SIZE]= '\n';
      ggc_block_cfb (&bbcc->BBCC_s_o2p, buffer, RANDOM_SIZE+1);
      write (bbcc->BBCC_socket, xmit_buffer, RANDOM_SIZE+1);

      bbcc->BBCC_status= BBCCst_ok;
      bbcc->BBCC_t2d= BBCCt2d_pushup;

      /* T2D: flush method! */
      /* T2D: shutdown method! */
      if (strcmp (bbcc->BBCC_resource, "shutdown") == 0)
      {
        bbc_sig_term (15);
        printf ("shutdown_flag set!\n");
        bbcc->BBCC_t2d= BBCCt2d_shutdown;
      }

      break;

    case BBCCst_initiator:
      buffer [buffer_size]= 0;
#ifdef DEBUGG1
      fprintf (stderr, ">>> opening string: '%s'\n", buffer);
#endif /* DEBUGG1 */
      rc= bbc_challenge (bbcs, bbcc, buffer);
#ifdef DEBUGG1
      fprintf (stderr, ">>> rc=%d\n", rc);
#endif /* DEBUGG1 */

      if (rc != 0) goto FAILED;

      /* BBC_CONNECTION */
      bbcc->BBCC_status= BBCCst_wait;
      sprintf (xmit_buffer,
               "BBC:CONNECT:%s:%s:%s:%s:%s:hi.\n",
               bbcc->BBCC_from, bbcc->BBCC_to,
               bbcc->BBCC_resource, bbcc->BBCC_chex_string,
               bbcc->BBCC_s_o2p.GGC_challenge);
      write (bbcc->BBCC_socket, xmit_buffer, strlen (xmit_buffer));
      return 0;

    case BBCCst_wait:
      if (strncmp (buffer, "BBC:OK:", 7) != 0) goto FAILED;

      /* set session key for communication from peer to this object */
      ggc_set_session_key (&bbcc->BBCC_s_p2o, bbcs->BBCS_key_file,
                           bbcc->BBCC_from, bbcc->BBCC_to,
                           bbcc->BBCC_resource);

      /* set session key for communication from this object to peer */
      ggc_set_session_key (&bbcc->BBCC_s_o2p, bbcs->BBCS_key_file,
                           bbcc->BBCC_from, bbcc->BBCC_to,
                           bbcc->BBCC_resource);

      bbcc->BBCC_status= BBCCst_initiator_wait_random;

      mk_PassWord (xmit_buffer, RANDOM_SIZE);
      xmit_buffer [RANDOM_SIZE]= '\n';
      ggc_block_cfb (&bbcc->BBCC_s_o2p, buffer, RANDOM_SIZE+1);
      write (bbcc->BBCC_socket, xmit_buffer, RANDOM_SIZE+1);
#ifdef DEBUGG1
      bbc_diag_conn (stdout, bbcc);
#endif /* DEBUGG1 */
      return 0;

    case BBCCst_initiator_wait_random:
      /* This is the initiatar which waits for the target to send           */
      /* its block of random data.                                          */
      /* After that, the communication channel is set up completely.        */

      /* T2D: does not check if the buffer has the right size!              */

      ggc_block_cfb (&bbcc->BBCC_s_p2o, buffer, buffer_size);
      bbcc->BBCC_status= BBCCst_ok;
      bbcc->BBCC_t2d= BBCCt2d_pushup;
      break;

    case BBCCst_ok: /* incoming data */
      ggc_block_cfb (&bbcc->BBCC_s_p2o, buffer, buffer_size);

#ifdef DEBUGG1
      buffer [buffer_size]= 0;
      fprintf (stderr, ">>> data: %s\n", buffer);
#endif /* DEBUGG1 */
      if ((input_handler= bbcc->BBCC_input2) != (BBC_input *) 0)
      {
/** fprintf (stderr, "input_handler=0x%08lX\n", input_handler); **/
        (*input_handler) (client_data, buffer, buffer_size);
      }
      return 0;

    case BBCCst_failed:
      buffer [buffer_size]= 0;
      fprintf (stderr, ">>> junk: %d bytes\n", buffer_size);
      dump (stderr, buffer, buffer_size);
      return 0;

    default:
      fprintf (stderr, "bbc04: internal error\n");
      return -1;
  }

  return 0;
}

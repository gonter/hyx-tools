/*
 *  include FILE <gg/bbch.h>
 *
 *  Black Board Controller
 *
 *  for information see %lexicon/bbcd.doc
 *
 *  - constants
 *  - methods:          typedef's for function prototyes
 *  - structures
 *  - macros
 *  - prototypes
 *
 *  written:       1995-08-03
 *  latest update: 1999-05-09 18:08:11
 *  $Id: bbch.h,v 1.4 2003/10/01 21:52:01 gonter Exp $
 *
 */

#ifndef __GG_bbch__
#define __GG_bbch__

#include <gg/parse.h>           /* @@@ import hyx_output_processor */
#include <gg/ggcrypt.h>
#include <gg/signatur.h>
#include <gg/floskel.h>

/* constants: ------------------------------------------------------------- */
#define MAX_HN_LNG 256
#define RANDOM_SIZE 23

/* methods: --------------------------------------------------------------- */
typedef int BBC_accept (void *client_data);
typedef int BBC_input (void *bbcc, char *block, int size);

/* structures: ------------------------------------------------------------ */
struct BBC_CONNECTION
{
  long sig;                     /* SIG_BBC_CONNECTION                       */
  struct BBC_CONNECTION *BBCC_next;
  void *BBCC_bbcs;              /* parrent session                          */

  int BBCC_status;
#define BBCCst_target    0      /* target side, waitinf for REQUEST message */
#define BBCCst_target2   1      /* target side, waiting for CONNECT message */
#define BBCCst_initiator 2      /* initiator side, waiting for ACCEPT msg.  */
#define BBCCst_wait      3      /* initiator waiting for BBC:OK:            */
#define BBCCst_ok        4      /* connection came up correctly identified  */
#define BBCCst_failed    5      /* other side could not be authenticated    */
#define BBCCst_initiator_wait_random 6
#define BBCCst_target_wait_random 7

  int BBCC_t2d;                 /* flag to indicate a special operation     */
#define BBCCt2d_nothing  0      /* ... everything's ok                      */
#define BBCCt2d_shutdown 1      /* ... this connection needs to be closed   */
#define BBCCt2d_pushup   2      /* authentication completed successfully    */

  /* peer entity information -- supplied by the peer                        */
  char *BBCC_from;              /* peer objects entity name                 */
  char *BBCC_to;                /* objects own entity name                  */
  char *BBCC_resource;          /* name of resource for this authentication */
  char *BBCC_opening_challenge; /* sent to initiator                        */
  char *BBCC_chex_string;       /* chex string returned by initiator        */

  struct GG_CRYPT               /* session streams encryption               */
    BBCC_s_o2p,                 /* encryption session to peer side          */
    BBCC_s_p2o;                 /* encryption session from peer side        */

  /* description of the peer connection                                     */
  int BBCC_connection_mode;     /* this structure is the same for initiator */
                                /* and called entity of a connection.       */
#define BBCCcm_undefined      0 /* initialized structure, no info yet       */
#define BBCCcm_called         1 /* this entity is called by the peer        */
#define BBCCcm_initiator      2 /* this entity is calling the peer          */
  char *BBCC_peer_host;         /* name of the peer's host, if known        */
  char *BBCC_peer_ipnum;        /* ip address of the peer's host            */
  long BBCC_peer_port;          /* port number of the peer, if known        */

  int BBCC_socket;              /* socket number                            */

  /* inherited data from session controller                                 */
  BBC_accept *BBCC_accept;

  BBC_input *BBCC_input1;       /* security layer input handler             */
  BBC_input *BBCC_input2;       /* processing layer input handler           */
  void *BBCC_client_data1;

  hyx_output_processor *BBCC_op;/* lexicon output processor                 */
} ;

/* ------------------------------------------------------------------------ */
struct BBC_LISTEN
{
  long sig;                     /* SIG_BBC_LISTEN                           */
  struct BBC_LISTEN *BBCL_next;
  void *BBCL_bbcs;              /* parrent session                          */

  int BBCL_socket;
} ;

/* ------------------------------------------------------------------------ */
struct BBC_SESSION
{
  long sig;                     /* SIG_BBC_SESSION                          */

  struct BBC_CONNECTION
    *BBCS_connections;          /* list of currently active connections     */
  int BBCS_count;               /* number of active connections             */

  int BBCS_is_public;           /* 1 -> this is a public resource           */
  char *BBCS_key_file;          /* file with chex keys                      */
  char *BBCS_my_name;           /* object name of this object               */
  char *BBCS_my_resource;       /* my object resource name (NOT USED???)    */
  char *BBCS_public_resource;   /* name of any public resource              */

  BBC_accept *BBCS_accept;

  /* connection information passed to established connections.              */
  BBC_input *BBCS_input1;       /* security layer input handler             */
  BBC_input *BBCS_input2;       /* processing layer input handler           */

  void *BBCS_client_data1;
  hyx_output_processor *BBCS_op;/* lexicon output processor                 */

#define BBCS_BUFFER_SIZE 8192
  char BBCS_buffer [BBCS_BUFFER_SIZE+2];
} ;

/* macros: ---------------------------------------------------------------- */
#define bbc_new_connection() \
  ((struct BBC_CONNECTION *) calloc (sizeof (struct BBC_CONNECTION), 1))

/* prototypes: ------------------------------------------------------------ */
/* bbc01.c */ void bbc_sig_term (int sig);
              int bbc_main (struct BBC_SESSION *bbcs, char *server, int port,
                int proc_stdin, char *target_name, char *target_resource);
/* bbc02.c */ void inet_netnames (int sockfd, char *host_name, char *ipnum);
/* bbc03.c */ struct BBC_CONNECTION *bbc_init_connection (
                struct BBC_SESSION *bbcs, int sock);
/* bbc04.c */ int bbc_authentication_protocol (void *client_data,
                char *buffer, int buffer_size);
/* bbc05.c */ int bbc_chex (struct BBC_SESSION *bbcs,
                struct BBC_CONNECTION *bbcc, char *buffer);

#ifdef _FILE_DEFINED
/* bbc06.c */ int bbc_diag_conn (FILE *fo, struct BBC_CONNECTION *bbcc);
#endif /* _FILE_DEFINED */

/* bbc07.c */ int bbc_lexicon_processor (void *client_data,
                char *buffer, int buffer_size);
/* bbc08.c */ int bbc_get_request (struct BBC_CONNECTION *bbcc, char *buffer);
/* bbc09.c */ struct BBC_LISTEN *bbc_server (int port);
/* bbc10.c */ struct BBC_CONNECTION *bbc_connect (
                struct BBC_SESSION *bbcs, char *server, int port,
                char *target_name, char *target_resource);
/* bbc11.c */ int bbc_challenge (struct BBC_SESSION *bbcs,
                struct BBC_CONNECTION *bbcc, char *buffer);
/* bbc12.c */ int bbc_to_stdout (void *client_data,
                char *buffer, int buffer_size);
/* bbc13.c */ int bbc_transmit_text (void *cd, struct TEXT_ELEMENT *te);
/* bbc14.c */ struct BBC_SESSION *bbc_new_session (void);
/* bbc15.c */ int bbc_acceptor (void *client_data);

#endif /* __GG_bbch__ */

/*
 *  FILE %ds/bbc/bbc.c
 *
 *  Black Board Controller
 *  - HELP
 *
 *  written:       1995-08-03
 *  latest update: 1999-05-09 18:03:20
 *  $Id: bbc.c,v 1.4 2003/06/25 10:11:44 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/dpp.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
#define GPL
static char *HELP []=
{
  "USAGE: bbc [options]\n",
  "  Black Board Controller\n",
  "OPTIONS:\n",
  "  -a       ... anonymous (PUBLIC challenge, OPEN encryption)\n",
  "  -h<host> ... host name to connect to\n",
  "  -p<num>  ... port number\n",
  "  -d       ... operate as daemon\n",
  "  -i       ... ignore stdin\n",
  "  -k<fnm>  ... key file name\n",
  "  -f<name> ... name of my object (from)\n",
  "  -t<name> ... name of the target object (to)\n",
  "  -r<name> ... name of the target resource (what)\n",
  "  -v       ... verbose mode\n",
  "\n",
  "(@)Abbc.c 1.03 #D$1995-08-21 12:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  struct BBC_SESSION *bbcs;
  int verbose_mode= 0;
#define OP_MODE_undef  0
#define OP_MODE_daemon 1
#define OP_MODE_client 2
  int op_mode= OP_MODE_undef;
  int port_number= 12345;
  int proc_stdin= 1;
  int is_public= 0;
  char *arg;
  char *key_file= ".kredenz.tfb";
  char *host_name= (char *) 0;
  char *my_name= "bbc.c";
  char *target_name= (char *) 0;
  char *target_resource= (char *) 0;
  char *my_resource= (char *) 0;
  char *public_resource= "urxn";

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
    {
      char *arg2= arg+2;

      switch (arg [1])
      {
        case 'a': case 'A':
          is_public= 1;
          break;

        case 'h': case 'H':
          op_mode= OP_MODE_client;
          host_name= arg2;
          break;

        case 'k': case 'K':
          key_file= arg2;
          break;

        case 'f': case 'F':
          my_name= arg2;
          break;

        case 't': case 'T':
          target_name= arg2;
          break;

        case 'r': case 'R':
          target_resource= arg2;
          break;

        case 'p': case 'P':
          if (*arg2 == 0) break;
          port_number= (int) get_parameter_value (arg2);
          break;

        case 'd': case 'D':
        case 'i': case 'I':
        case 'v': case 'V':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'd': case 'D':
                op_mode= OP_MODE_daemon;
                break;
              case 'i': case 'I':
                proc_stdin= 0;
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", arg [j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    }
  }

  if ((bbcs= bbc_new_session ()) == (struct BBC_SESSION *) 0)
  {
    fprintf (stderr, "could not establish BBC session\n");
    return -1;
  }

  switch (op_mode)
  {
    case OP_MODE_daemon:
    case OP_MODE_client:
      bbcs->BBCS_key_file=        key_file;
      bbcs->BBCS_my_name=         my_name;
      bbcs->BBCS_my_resource=     my_resource;
      bbcs->BBCS_public_resource= public_resource;

      bbc_main (bbcs, host_name, port_number, proc_stdin,
                target_name, target_resource);
      break;

    default:
      goto HLP;
  }

  return 0;
}

/*
 *  FILE %sgml/hyxd01.c
 *
 *  Hypertext daemon
 *
 *  written:       1992 12 08
 *  latest update: 1999-04-24 11:53:13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/ggcrypt.h>
#include <gg/hyxd.h>

/* ------------------------------------------------------------------------ */
int hyx_d_daemon (
FILE *fi,                               /* input stream         */
FILE *fo,                               /* output stream        */
char *cluster,
char *credential_file)
{
  int rc;
  struct HYXD_THREAD *thr;
  char *line;
  int authenticated= 0;
  int authentication_phase= 0;
#define N_TOKENS 4
  char *tokens [N_TOKENS];
#define CHALLENGE_SIZE 16
  char challenge [CHALLENGE_SIZE+1];
  char *challenge_string= (char *) 0;
  char *user_from, *user_to, *resource;

  if ((thr= hyx_d_new_thread ()) == (struct HYXD_THREAD *) 0
      || (thr->hcc= hyx_new_cluster_control ())
             == (struct HYX_CLUSTER_CONTROL *) 0
     )
    return -1;

  thr->fi= fi;
  thr->fo= fo;
  line= thr->line;

  if (credential_file == (char *) 0) authenticated= 1;

  if (cluster != (char *) 0) 
  {
    char *afn;

    if ((afn= translate_logic_filename (cluster)) == (char *) 0) return -1;
    hcc_set_cluster_name (thr->hcc, afn);
    free_or_what (afn);
    thr->hcc_defined= 1;
  }

  for (;;)
  {
    rc= fread_line (fi, line, HYXD_LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;
    if (line [0] == '#') continue;

    if (!authenticated)
    {
      rc= isolate_tokens (line, tokens, N_TOKENS);
      if (rc <= 0 || strcmp (tokens [0], "CHEX") != 0) break;

      switch (authentication_phase)
      {
        case 0:
          /* Protocol:                          */
          /*   Request: CHEX from to resource   */
          /*   Answer:  OK challenge | ERROR    */
          authentication_phase= -1;

          if (rc != 4) break;

          user_from= tokens [1];
          user_to=   tokens [2];
          resource=  tokens [3];

          mk_PassWord (challenge, CHALLENGE_SIZE);
          fprintf (fo, "OK %s\n", challenge);
          authentication_phase= 1;
          break;

        case 1:
          /* Protocol:                          */
          /*   Request: CHEX chex-string        */
          /*   Answer:  OK | ERROR              */
          authentication_phase= -1;

          if (rc == 2
              && (challenge_string=
                    agettok_get_challenge (credential_file,
                       user_from, user_to, resource, challenge))
                   != (char *) 0
              && strcmp (challenge_string, tokens [1]) == 0
             )
          {
            authenticated= 1;
            authentication_phase= 2;
            fprintf (fo, "OK\n");
          }
          break;
      }

      if (authentication_phase == -1)
      {
        fprintf (fo, "ERROR\n");
        break;
      }
      continue;
    }

    if (hyx_d_command (thr, line) == 1) break;
  }

  /* destroy thread */
  hcc_close (thr->hcc);
  hcc_destroy (thr->hcc);
  free (thr);

  return 0;
}

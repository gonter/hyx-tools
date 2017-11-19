/*
 *  FILE %ds/ggcrypt/ggcryp14.c
 *
 *  written:       1995-08-06
 *  latest update: 1996-05-06  1:17:46
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/ggcrypt.h>

static char OPEN []= "OPEN";

/* ------------------------------------------------------------------------ */
int ggc_set_session_key (
struct GG_CRYPT *ggc,
char *key_file,
char *from,
char *to,
char *resource)
{
  char *challenge;
  char *chex_string;
  char *session_key;

  if (ggc == (struct GG_CRYPT *) 0) return -1;

  challenge= ggc->GGC_challenge;
  ggc->GGC_key= (char *) 0;
  ggc->GGC_index= 0;

  if (strcmp (challenge, OPEN) != 0)
  { /* generate session key */
    if ((session_key= malloc (20)) == (char *) 0) return -1;

    if ((chex_string= agettok_get_challenge (key_file, from, to,
                        resource, challenge)) == (char *) 0)
      return -1;

    hex_to_bin (chex_string, session_key, 32);

    ggc->GGC_key= session_key;
    ggc->GGC_key_str= strdup (chex_string);
  }

  return 0;
}

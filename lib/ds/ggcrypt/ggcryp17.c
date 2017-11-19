/*
 *  FILE %ds/ggcrypt/ggcryp17.c
 *
 *  written:       1996-08-11
 *  latest update: 1997-02-28  0:05:35
 *
 */

#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_dispose_key (struct GG_CRYPT *ggc)
{
  if (ggc == (struct GG_CRYPT *) 0) return -1;

  ggc_dispose_block (&ggc->GGC_key,       KEYED_MD5_SIZE-1);
  ggc_dispose_block (&ggc->GGC_key_str,   0);
  ggc_dispose_block (&ggc->GGC_challenge, 0);

  return 0;
}

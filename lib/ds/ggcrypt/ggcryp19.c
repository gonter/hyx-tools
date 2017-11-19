/*
 *  FILE %ds/ggcrypt/ggcryp19.c
 *
 *  written:       1996-08-11
 *  latest update: 1996-08-11 18:53:59
 *
 */

#include <stdlib.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_dispose (struct GG_CRYPT *ggc)
{
  if (ggc_dispose_key (ggc) == 0) free (ggc);

  return 0;
}

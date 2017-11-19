/*
 *  FILE %ds/ggcrypt/ggcryp13.c
 *
 *  written:       1995-08-02
 *  latest update: 1997-10-05  9:49:45
 *  $Id: ggcryp13.c,v 1.2 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_block_encrypt (
struct GG_CRYPT *ggc,
char *buffer,
int size)
{
  int idx;
  int u, e, k;
  char *key;

  if (ggc == (struct GG_CRYPT *) 0) return -1;

  if ((key= ggc->GGC_key) == (char *) 0) return 0;      /* no encryption    */

  if ((idx= ggc->GGC_index) < 0) idx= 0;                /* well...          */

  for (; size > 0; size--)
  {
    if (idx >= 16) idx= 0;

    e= *buffer & 0x00FF;
    k= key [idx] & 0x00FF;

    u= e ^ k;

#ifdef MODE_CFB
    key [idx]= (char) (k+1 & 0x00FF);
#endif

    *buffer++= (char) u;
    idx++;
  }

  ggc->GGC_index= idx;

  return 0;
}

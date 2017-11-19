/*
 *  FILE %ds/ggcrypt/ggcryp16.c
 *
 *  written:       1996-05-06
 *  latest update: 1996-08-12 19:04:58
 *
 */

#include <stdlib.h>
#include <string.h>
#include <contrib/global.h>
#include <contrib/md5.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
struct GG_CRYPT *ggc_set_key (
struct GG_CRYPT *ggc,
char *key)
{
  unsigned char *digest;
  MD5_CTX context;

  if ((ggc == (struct GG_CRYPT *) 0
       && (ggc= calloc (sizeof (struct GG_CRYPT), 1)) == (struct GG_CRYPT *) 0
      )
      || (digest= malloc (KEYED_MD5_SIZE)) == (unsigned char *) 0
     )
   return (struct GG_CRYPT *) 0;

  MD5Init (&context);
  MD5Update (&context, (unsigned char *) key, strlen (key));
  MD5Final (digest, &context);

  ggc->GGC_key= (char *) digest;
  ggc->GGC_index= 0;

  return ggc;
}

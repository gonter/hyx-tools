/*
 *  FILE %ds/ggcrypt/ggcryp07.c
 *
 *  written:       1995-04-27
 *  latest update: 1996-08-08 17:19:45
 *
 */

#include <string.h>
#include <gg/dpp.h>
#include <gg/ggcrypt.h>
#include <contrib/global.h>
#include <contrib/md5.h>
#include <contrib/md5gg.h>

static char *delim= ":";
static int delim_size= 1;

/* ------------------------------------------------------------------------ */
char *sec_generate_key (
char *principal,                /* who is it                                */
char *resource,                 /* what is wanted                           */
char *identifier,               /* challenge                                */
char *secret)                   /* actuall password                         */
{
  MD5_CTX context;
  unsigned char digest [16];    /* message digest                           */
  char md5_str [34];            /* token                                    */

  MD5Init (&context);

  MD5Update (&context, (unsigned char *) principal,  strlen (principal));
  MD5Update (&context, (unsigned char *) delim,      delim_size);
  MD5Update (&context, (unsigned char *) resource,   strlen (resource));
  MD5Update (&context, (unsigned char *) delim,      delim_size);
  MD5Update (&context, (unsigned char *) identifier, strlen (identifier));
  MD5Update (&context, (unsigned char *) delim,      delim_size);
  MD5Update (&context, (unsigned char *) secret,     strlen (secret));

  MD5Final (digest, &context);
  bin_to_hex ((char *) digest, md5_str, 16);

  return strdup (md5_str);
}

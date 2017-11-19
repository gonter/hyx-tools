/*
 *  FILE %ds/ggcrypt/ggcryp06.c
 *
 *  written:       1994-10-23
 *  latest update: 1996-08-08 16:44:56
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggcrypt_string (
unsigned char *string,
unsigned char *key,
int key_lng)
{
  return ggcrypt_block (string, strlen ((char *) string), key, key_lng);
}

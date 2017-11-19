/*
 *  FILE ~/usr/sbr/ggcryp05.c
 *
 *  written:       1994-10-23
 *  latest update: 1995-04-27
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggcrypt_block (
unsigned char *block,
int block_lng,
unsigned char *key,
int key_lng)
{
  unsigned char *kp;
  int kl;

  if (block == (unsigned char *) 0 || key == (unsigned char *) 0) return -1;
  if (key_lng == 0) return 0;

  kp= key;
  kl= key_lng;

  while (block_lng-- > 0)
  {
    *block= *block ^ *kp;
    if (--kl == 0)
    {
      kp= key;
      kl= key_lng;
    }
    block++;
    kp++;
  }

  return 0;
}

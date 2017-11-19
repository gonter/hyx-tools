/*
 *  FILE %ds/ggcrypt/ggcryp11.c
 *
 *  AFS shortcut authentication
 *
 *  written:       1995-05-10
 *  latest update: 1999-05-30 18:32:49
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/ggcrypt.h>
#include <gg/dpp.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
char *sca_get_signature (char *username, char *password)
{
  char *sig;
  unsigned char *dig;
#define N_STR 3
  unsigned char *str [N_STR];
  int lng [N_STR];

  if (username == (char *) 0 || *username == 0
      || password == (char *) 0 || *password == 0
      || (sig= (char *) malloc (34)) == (char *) 0
     ) return (char *) 0;

  str [0]= (unsigned char *) username;          lng [0]= strlen (username);
  str [1]= (unsigned char *) ":";               lng [1]= 1;
  str [2]= (unsigned char *) password;          lng [2]= strlen (password);

  dig= MD5chk2_block_array (str, lng, N_STR);
  bin_to_hex ((char *) dig, sig, 16);

  return sig;
}

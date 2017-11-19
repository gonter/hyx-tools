/*
 *  FILE %ds/ggcrypt/ggcryp15.c
 *
 *  simple file encryption algorithms
 *  see: ggc_block_ecb, ggc_block_cfb
 *
 *  written:       1995-08-15
 *  latest update: 1997-10-05  9:42:17
 *  $Id: ggcryp15.c,v 1.3 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_file_encrypt (
struct GG_CRYPT *ggc,
char *fn,                       /* name of file to encrypt/decrypt          */
char *crypt_tmp,                /* name of temporary file                   */
long padding)                   /* > 0L: add this many bytes at the         */
                                /*       beginning of the encrypted         */
                                /*       stream                             */
                                /* < 0L: decrypt and discard this many      */
                                /*       bytes from the beginning of        */
                                /*       the stream                         */
{
  FILE *fi= (FILE *) 0;
  FILE *fo= (FILE *) 0;
  int rv= -2;
  int fi_open= 0;
  int fo_open= 0;

  if (strcmp (fn, "-") == 0) fi= stdin;
  else
  if ((fi= fopen (fn, "rb")) != (FILE *) 0) fi_open= 1;
  else
  {
    fprintf (stderr, "can't read from file %s!\n", fn);
    goto STOP;
  }

  if (strcmp (crypt_tmp, "-") == 0) fo= stdout;
  else
  if ((fo= fopen (crypt_tmp, "wb")) != (FILE *) 0) fo_open= 1;
  else
  {
    fprintf (stderr, "can't write to file %s!\n", crypt_tmp);
    goto STOP;
  }

  /* [1997-10-05] encryption engine isolated */
  rv= ggc_stream_encrypt (ggc, fi, fo, padding);

STOP:
  if (fi_open && fi != (FILE *) 0) fclose (fi);
  if (fo_open && fo != (FILE *) 0) fclose (fo);

  return rv;
}

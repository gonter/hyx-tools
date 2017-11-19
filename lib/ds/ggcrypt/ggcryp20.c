/*
 *  FILE %ds/ggcrypt/ggcryp20.c
 *
 *  simple file encryption algorithms
 *  see: ggc_block_ecb, ggc_block_cfb, ggc_file_ecb, ggc_file_cfb
 *
 *  written:       1997-10-05 [extracted from ggcryp15.c]
 *  latest update: 1997-10-05  9:36:36
 *  $Id: ggcryp20.c,v 1.3 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>

#define BS GGC_BUFFER_SIZE

/* ------------------------------------------------------------------------ */
int ggc_stream_encrypt (
struct GG_CRYPT *ggc,
FILE *fi,                       /* input stream                             */
FILE *fo,                       /* output stream                            */
long padding)                   /* > 0L: add this many bytes at the         */
                                /*       beginning of the encrypted         */
                                /*       stream                             */
                                /* < 0L: decrypt and discard this many      */
                                /*       bytes from the beginning of        */
                                /*       the stream                         */
{
  char *buffer= (char *) 0;
  int rv= -2;
  int rc;

  if ((buffer= malloc (BS)) == (char *) 0)
  {
    fprintf (stderr, "can't allocate buffer!\n");
    goto STOP;
  }

  ggc_pad (ggc, fo, buffer, padding, BS);

  /* negative padding value: decrypt cyphertext and discard it */
  if (padding < 0L)
  {
    padding= -padding;
    for (; padding > 0L; padding -= (long) rc)
    {
      rc= (padding > BS) ? BS : (int) padding;
      rc= fread (buffer, 1, rc, fi);

      if (rc <= 0)
      {
        fprintf (stderr, "can't remove padded block!\n");
        goto STOP;
      }

      ggc_block_encrypt (ggc, buffer, rc);
    }
  }

  for (;;)
  {
    rc= fread (buffer, 1, BS, fi);
    if (rc <= 0) break;

    ggc_block_encrypt (ggc, buffer, rc);
    fwrite (buffer, 1, rc, fo);
  }

  rv= 0;        /* all went fine, set OK result code */

STOP:
  free_or_what (buffer);

  return rv;
}

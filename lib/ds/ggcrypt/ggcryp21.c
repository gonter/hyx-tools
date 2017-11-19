/*
 *  FILE %ds/ggcrypt/ggcryp21.c
 *
 *  simple file encryption algorithms
 *  see: ggc_block_cfb
 *
 *  written:       1997-10-05
 *  latest update: 1997-10-05  9:36:36
 *  $Id: ggcryp21.c,v 1.1 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/attlist.h>
#include <gg/ggcrypt.h>

#define BS GGC_BUFFER_SIZE

/* ------------------------------------------------------------------------ */
int ggc_stream_2encrypt (
struct GG_CRYPT *ggc,
FILE *fi,                       /* input stream                             */
FILE *fo,                       /* output stream                            */
ATTLIST *al_pre,
ATTLIST *al_post,
long padding1,
long padding2)
{
  char *buffer= (char *) 0;
  int rv= -1;
  int rc;

  if ((buffer= malloc (BS)) == (char *) 0)
  {
    fprintf (stderr, "can't allocate buffer!\n");
    goto STOP;
  }

  ggc_pad (ggc, fo, buffer, padding1, BS);
  ggc_wr_tag_block (ggc, fo, "CH", al_pre, buffer);

  for (;;)
  {
    rc= fread (buffer, 1, BS, fi);
    if (rc <= 0) break;

    ggc_block_encrypt (ggc, buffer, rc);
    fwrite (buffer, 1, rc, fo);
  }

  ggc_wr_tag_block (ggc, fo, "CT", al_post, buffer);
  ggc_pad (ggc, fo, buffer, padding2, BS);

  rv= 0;        /* all went fine, set OK result code */

STOP:
  free_or_what (buffer);

  return rv;
}

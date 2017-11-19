/*
 *  FILE %ds/ggcrypt/ggcryp23.c
 *
 *  simple file encryption algorithms
 *
 *  written:       1997-10-05
 *  latest update: 1997-10-05  9:36:36
 *  $Id: ggcryp23.c,v 1.2 2007/12/02 11:58:09 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
void ggc_pad (struct GG_CRYPT *ggc, FILE *fo, char *buffer, long padding, long BS)
{
  long len;

  /* positive padding value: generate random clear text */
  for (; padding > 0L; padding -= (long) len)
  {
    len= (padding > BS) ? BS : (int) padding;
    mk_PassWord (buffer, len);

    ggc_block_encrypt (ggc, buffer, len);
    fwrite (buffer, 1, len, fo);
  }
}

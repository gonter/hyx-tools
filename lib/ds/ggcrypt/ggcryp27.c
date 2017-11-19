/*
 *  FILE %ds/ggcrypt/ggcryp27.c
 *
 *  simple file encryption algorithms, see ggc_pad in ggcryp23.c
 *
 *  written:       2007-12-02
 *  latest update: 2007-12-02 11:11:33
 *  $Id: ggcryp27.c,v 1.2 2007/12/02 12:30:57 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <contrib/global.h>
#include <contrib/md5.h>
#include <contrib/md5gg.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
long ggc_pad_md5
(
  struct GG_CRYPT *ggc,
  MD5_CTX *md5,
  FILE *fo,
  char *buffer,
  long padding,
  long BS
)
{
  long len;
  long rc= 0L;

  /* positive padding value: generate random clear text */
  for (; padding > 0L; padding -= (long) len)
  {
    long wl;

    len= (padding > BS) ? BS : (int) padding;

    mk_PassWord (buffer, (int) len);
    ggc_block_encrypt (ggc, buffer, len);

    rc += wl= fwrite (buffer, 1, len, fo);

    /* update after write to get correct md5 sum when filesystem is full */
    MD5Update (md5, buffer, wl);

    if (wl != len) break;
  }

  return rc;
}

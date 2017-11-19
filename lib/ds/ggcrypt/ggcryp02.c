/*
 *  FILE %sbr/ggcryp02.c
 *
 *  simple file encryption algorithms
 *
 *  written:       1990 08 25
 *                 1994-09-18: extracted from %usr/utl/crypt.c
 *  latest update: 1995-08-15
 *
 */

#include <stdio.h>
#include <gg/ggcrypt.h>

#ifdef MODE_ENCRYPT
#define gg_xxx_crypt gg_encrypt
#endif /* MODE_ENCRYPT */

#ifdef MODE_DECRYPT
#define gg_xxx_crypt gg_decrypt
#endif /* MODE_DECRYPT */

#ifdef MODE_SIMPLE
#define gg_xxx_crypt ggcrypt_very_simple
#endif /* MODE_SIMPLE */

/* ------------------------------------------------------------------------ */
int gg_xxx_crypt (
char *fn,
#ifdef MODE_SIMPLE
char *crypt_code,
#endif /* MODE_SIMPLE */
int crypt_length,
char *crypt_tmp,
char *buffer1,
char *buffer2,
int BUFFER_SIZE)
{
  FILE *fi, *fo;
  int ch;
  int crypt_idx= 0;

  if (crypt_length <= 0)
  {
    fprintf (stderr, "no encryption code specified for %s!\n", fn);
    return -1;
  }

  if ((fi= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "can't read from file %s!\n", fn);
    return -2;
  }

  if ((fo= fopen (crypt_tmp, "wb")) == (FILE *) 0)
  {
    fprintf (stderr, "can't write to file %s!\n", crypt_tmp);
    return -2;
  }

  setvbuf (fi, buffer1, _IOFBF, BUFFER_SIZE);
  setvbuf (fo, buffer2, _IOFBF, BUFFER_SIZE);

  for (;;)
  {
#ifdef MODE_ENCRYPT
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    ggcrypt_fputc_code (ch, fo);
#endif /* MODE_ENCRYPT */

#ifdef MODE_DECRYPT
    ch= ggcrypt_fgetc_code (fi) & 0x00FF;
    if (feof (fi)) break;
    fputc (ch, fo);
#endif /* MODE_DECRYPT */

#ifdef MODE_SIMPLE
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    ch ^= crypt_code [crypt_idx++];
    if (crypt_idx >= crypt_length) crypt_idx= 0;
    fputc (ch, fo);
#endif /* MODE_SIMPLE */
  }

#ifdef MODE_ENCRYPT
  ggcrypt_flush_last (fo);
#endif /* MODE_ENCRYPT */

  fclose (fi);
  fclose (fo);

  unlink (fn);
  rename (crypt_tmp, fn);

  return 0;
}

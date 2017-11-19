/*
 *  FILE %ds/ggcrypt/ggcryp21.c
 *
 *  simple file encryption algorithms
 *  see: ggc_block_cfb
 *
 *  written:       1997-10-05
 *  latest update: 1997-10-05  9:36:36
 *  $Id: ggcryp26.c,v 1.1 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/attlist.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_wr_tag_block (
struct GG_CRYPT *ggc,
FILE *fo,
char *tag_name,
ATTLIST *al,
char *buffer)
{
  int cnt= 0;
  struct ATTRIBUTE_LIST *alp;
  int c;

  c= sprintf (buffer, "<%.32s>\n", tag_name);
  ggc_block_encrypt (ggc, buffer, c);
  fwrite (buffer, 1, c, fo);
  cnt += c;

  if (al != (ATTLIST *) 0)
  {
   for (alp= al->AL_start; alp != (struct ATTRIBUTE_LIST *) 0; alp= alp->AL_next)
   {
    switch (alp->AL_type)
    {
      case ALty_string:
      case ALty_string_dup:
        c= sprintf (buffer, "<%.32s>%.8100s\n", alp->AL_name, (char *) alp->AL_value);
        break;

      case ALty_long:
        c= sprintf (buffer, "<%.32s>%ld\n", alp->AL_name, (long) alp->AL_value);
        break;
    }

    ggc_block_encrypt (ggc, buffer, c);
    fwrite (buffer, 1, c, fo);
    cnt += c;
   }
  }

  c= sprintf (buffer, "</%.32s>", tag_name);
  ggc_block_encrypt (ggc, buffer, c);
  fwrite (buffer, 1, c, fo);
  cnt += c;

  return cnt;
}

/*
 *  FILE %ds/dyb/dyb_0008.c
 *
 *  manipulation of dynamic blocks:
 *
 *  written:       1995-08-19
 *  latest update: 1996-05-06  1:08:49
 *
 */

#include <gg/ggcrypt.h>
#include <gg/dyb.h>

#ifdef MODE_ECB
/* electronic coodebook mode */
#define dyb_encrypt dyb_encrypt_ecb
#define ggc_block_encrypt ggc_block_ecb
#endif

#ifdef MODE_CFB
/* cipher feedback mode */
#define dyb_encrypt dyb_encrypt_cfb
#define ggc_block_encrypt ggc_block_cfb
#endif

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_encrypt (
struct GG_CRYPT *ggc,
struct DYNAMIC_BLOCK *dyb)
{
  struct DYB_SEGMENT *ds;

  if (dyb == (struct DYNAMIC_BLOCK *) 0
      || ggc == (struct GG_CRYPT *) 0
     ) return -1;

  if (ggc->GGC_key == (char *) 0) return 0; /* no encryption, ok...  */

  for (ds= dyb->DYB_begin;
       ds != (struct DYB_SEGMENT *) 0;
       ds= ds->DYBS_next)
  {
    if (ggc_block_encrypt (ggc, ds->DYBS_block,
                           (int) (ds->DYBS_size - ds->DYBS_free)) != 0)
      return -1;
  }

  return 0;
}

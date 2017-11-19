/*
 *  FILE ~/usr/nl_kr/lib/nl_00106.c
 *
 *  deref a word
 *
 *  written:       1993-03-27: extracted from nl_00104.c
 *  latest update: 1995-07-30
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int lmd_deref_word_ref (
struct LMD_QUERY_SET *lmdqs,
char *w,
int exact,
struct WORD_REF_LIST **wrl)
{
  long w_info;
  int lng;
  int rc;
  FILE *f_lut;

#ifdef DEBUG
printf ("nl_00106: w='%s' exact=%d\n", w, exact);
#endif /* DEBUG */

  f_lut= lmdqs->LMDQS_F_lt;
  lmdqs->LMDQS__wrl= wrl;
  lmdqs->LMDQS__error_flag= 0;

  fseek (f_lut, 0L, 0);

  if (w != (char *) 0 && *w == 0 && !exact)
  {
    lmdqs->LMDQS_pfx= "";
    lmdqs->LMDQS_pfx_lng= 0;
    goto PROCESS;
  }

  if ((rc= lookup_file (f_lut, w, &w_info, &lng)) < 0) return -1;

#ifdef DEBUG
printf ("nl_00106: lookup('%s') =: rc=%d, lng=%d\n", w, rc, lng);
#endif /* DEBUG */

  if (((rc & LOOKUP_found) && exact)
      || ((rc & LOOKUP_prefix_3) && !exact))
  {
    char *wrd;

    wrd= lut_file_get_word_buffer ();
    lmdqs->LMDQS_pfx= (char *) 0;
    lmdqs->LMDQS_pfx_lng= 0;

#ifdef DEBUG
printf ("nl_00106: store exact word info\n", w, rc, lng);
#endif /* DEBUG */

    lmd_store_word_ref (wrd, w_info, (void *) lmdqs);
  }

  if (!exact && ((rc & LOOKUP_prefix_4) || ((rc & LOOKUP_found))))
  {
    long off;

    if ((off= lut_file_get_dump_beg ()) != -1L)
    {
      lmdqs->LMDQS_pfx= lut_file_get_word_buffer ();
      lmdqs->LMDQS_pfx_lng= strlen (lmdqs->LMDQS_pfx);
      fseek (f_lut, off, 0);
PROCESS:
      lut_process_block (f_lut, lmd_store_word_ref, (void *) lmdqs);
    }
  }

  if (lmdqs->LMDQS__error_flag != 0) return -1;

  return 0;
}

/*
 *  FILE %nl_kr/lib/nl_00502.c
 *
 *  write word information structures
 *  - see lmd_read_tables (), handling of lmdd structure used there too
 *
 *  written:       1993-02-28
 *                 1994-12-18: isolated from  wordcr05.c
 *  latest update: 1996-12-22 17:48:59
 *  $Id: nl_00502.c,v 1.3 2001/08/26 23:26:03 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_write_tables (
struct LMDC_CONTROL *lmdc,
char *fn_wr,
char *fn_di,
int mode)
{
  FILE *fo_wr= (FILE *) 0;
  FILE *fo_di;
  struct LMDD_CONTROL *lmdd;
  int i;
  int rv= -1;

  if ((lmdd= (struct LMDD_CONTROL *)
                calloc (sizeof (struct LMDD_CONTROL), 1))
          == (struct LMDD_CONTROL *) 0
     ) return -1;

  if (mode == LMDD_mode_full)
  {
    if ((fo_wr= fopen (fn_wr, "wb")) == (FILE *) 0
        || (fo_di= fopen (fn_di, "wb")) == (FILE *) 0
       ) goto ERROR;

    /* write table headers */
    dpp_fwrite_long (fo_wr, (long) WORD_REF_SIZE, 4);
    for (i= WORD_REF_SIZE - 4; i > 0; i--) fputc (0xFF, fo_wr);

    dpp_fwrite_long (fo_di, (long) DOCUMENT_INFO_SIZE, 4);
    for (i= DOCUMENT_INFO_SIZE - 4; i > 0; i--) fputc (0xFF, fo_di);

    lmdd->LMDD_doc_items_offset= 1L;
  }
  else
  {
    struct stat st;
    int rc;
    long siz;

    if ((rc= stat (fn_di, &st)) != 0) goto ERROR;
    siz= st.st_size;
    siz /= DOCUMENT_INFO_SIZE;
    lmdd->LMDD_doc_items_offset= siz;
    if ((fo_di= fopen (fn_di, "ab")) == (FILE *) 0) goto ERROR;
  }

  /* initialize dump control structure  */
  lmdd->LMDD_lmdc= lmdc;
  lmdd->LMDD_fo_wr= fo_wr;
  lmdd->LMDD_fo_di= fo_di;
  lmdd->LMDD_doc_items_offset= 1L;
  lmdd->LMDD_items_written= 0L;
  lmdd->LMDD_word_index= 1L;
  lmdd->LMDD_mode= mode;

  lmd_print_lmdd (stdout, lmdd);
  ytree_process (lmdc->LMDC_ytree, lmd_dump_word_entry, lmdd);
  lmd_print_lmdd (stdout, lmdd);

  rv= 0;

  fclose (fo_di);
  fclose (fo_wr);

ERROR:
  free (lmdd);

  return rv;
}

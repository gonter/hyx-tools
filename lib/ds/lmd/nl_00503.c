/*
 *  FILE %ds/lmd/nl_00503.c
 *
 *  read word information structures
 *  - see lmd_write_tables () handling of lmdd structure take from there
 *
 *  written:       1993-02-28
 *                 1994-12-18: isolated from  wordcr05.c
 *  latest update: 1996-12-22 17:47:03
 *  $Id: nl_00503.c,v 1.4 2002/01/29 08:01:42 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long lmd_read_tables (
struct LMDC_CONTROL *lmdc,
char *fn_wr,
char *fn_di)
{
  FILE *fo_wr;
  FILE *fo_di;
  long word_ids;
  struct LMDD_CONTROL *lmdd;

#ifdef DEBUG
printf ("nl_00503.c: fn_wr='%s' fn_di='%s'\n", fn_wr, fn_di);
#endif

  if ((fo_wr= fopen (fn_wr, "rb")) == (FILE *) 0
      ||(fo_di= fopen (fn_di, "rb")) == (FILE *) 0
     ) return -1L;

/*******************
  word_ids= lmd_read_word_ref_list (fo_wr, fo_di, lmdc->LMDC_ytree
*****************/

  if ((lmdd= (struct LMDD_CONTROL *) calloc (sizeof (struct LMDD_CONTROL), 1))
      == (struct LMDD_CONTROL *) 0) return -1;

  /* setup dump control structure  */
  lmdd->LMDD_lmdc= lmdc;
  lmdd->LMDD_fo_wr= fo_wr;
  lmdd->LMDD_fo_di= fo_di;
  lmdd->LMDD_doc_items_offset= 1L;
  lmdd->LMDD_items_written= 0L;
  lmdd->LMDD_word_index= 1L;

  lmd_print_lmdd (stdout, lmdd);
  ytree_process (lmdc->LMDC_ytree, lmd_read_word_ref_list, lmdd);
  lmd_print_lmdd (stdout, lmdd);

  fclose (fo_di);
  fclose (fo_wr);

  word_ids= lmdd->LMDD_doc_items_written;
  free (lmdd);

  return word_ids;
}

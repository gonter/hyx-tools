/*
 *  FILE %ds/lmd/nl_00501.c
 *
 *  manipulate word information data structures
 *
 *  written:       1993-02-28
 *                 1994-12-18: isolated from  wordcr05.c
 *  latest update: 2001-02-04 20:33:38
 *  $Id: nl_00501.c,v 1.3 2001/02/06 20:06:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>

extern long YTREE_ALLOCATED;

/* ------------------------------------------------------------------------ */
int lmd_word_statistics (
struct LMDC_CONTROL *lmdc,
struct WORD_REF *wi,
char *string,
long document_id,
long document_ptr,
char *document_id_str,
int operation,
int loc_operator,
int loc_number,
long loc_code)
{
  struct DOCUMENT_INFO *di;
  struct YTREE *yt;

  if (document_id < 0L
      || wi->WR_count == -1L            /* don't count stop words           */
     ) return 0;

  if (++wi->WR_count >= lmdc->LMDC_max_word_count
      || document_id == 0L
     )
  {
    if (document_id > 0L && wi->WR_count == lmdc->LMDC_max_word_count)
      printf ("dropping stop word: '%s' count=%ld\n",
              (string == (char *) 0) ? "?" : string,
              wi->WR_count);

    if (operation == ADD_WORD_REF) operation= DEL_WORD_REF;
  }

  switch (operation)
  {
    case ADD_WORD_REF:
      if ((di= lmd_find_document_info (wi, document_id_str))
          == (struct DOCUMENT_INFO *) 0)
      {
        if ((di= lmd_insert_document_info (wi, document_id, document_id_str))
            == (struct DOCUMENT_INFO *) 0)
          return -1;

        wi->WR_docinfo_count++;
#ifdef LMD_EXTENDED_MODEL
        di->DI_document_ptr= document_ptr;
#endif /* LMD_EXTENDED_MODEL */
      }
      di->DI_hit_count++;
      /*** wi->WR_count++; ***/

#ifdef LMD_EXTENDED_MODEL
      /* put position code into place:          */
      /* see implementation notes about details */
      lmd_set_location_code (di, loc_operator, loc_number, loc_code);
#else
#ifdef MSDOS
      document_ptr; loc_operator; loc_number; loc_code;
#endif /* MSDOS */
#endif /* !LMD_EXTENDED_MODEL */
      break;

    case DEL_WORD_REF:
      if ((yt= wi->WR_ytree) != (struct YTREE *) 0)
      {
        long prev= YTREE_ALLOCATED;
        ytree_process (yt, lmd_discard_document_node, (void *) 0);
        ytree_free (yt);
        printf ("discarding WR_ytree ytree prev=%ld now=%ld\n",
                prev, YTREE_ALLOCATED);
        wi->WR_ytree= (struct YTREE *) 0;
      }
      /*** wi->WR_count= -1L; ***/
      break;

    default:
      return -1;
  }

  return 0;
}

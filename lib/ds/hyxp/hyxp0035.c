/*
 *  FILE %ds/hyxp/hyxp0035.c
 *
 *  written:       1991 03 17
 *  latest update: 1997-11-02 23:22:28
 *  $Id: hyxp0035.c,v 1.2 2003/06/25 10:11:56 gonter Exp $
 *
 */

#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long hyx_get_tag_definition (
struct HYX_PARSER_CLASS *hpc,
struct TEXT_ELEMENT *tx,
int append)
{
  struct TEXT_SEGMENT *txs;
  struct TAG_DEFINITION *td;

  switch ((int) tx->sig)
  {
    case SIG_TEXT_ELEMENT:
      txs= tx->TE_text_segment;
      break;
    case SIG_TEXT_SEGMENT:
      txs= (struct TEXT_SEGMENT *) tx;
      break;
    default:
      return -1L;
  }

  if (tx->sig == SIG_TEXT_ELEMENT
      && tx->TE_level > 0
      && (td= hyx_identify_tag (hpc, txs->TSEG_text_array, append))
         != (struct TAG_DEFINITION *) 0
     )
  {
    tx->TE_tag_definition= td;
    return td->tag_id;
  }

  return 0L;
}

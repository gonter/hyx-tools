/*
 *  FILE %ds/hyxp/hyxp0028.c
 *
 *  a new text element can be created with buffered data
 *
 *  written:       1995-12-21
 *  latest update: 1997-11-02 22:38:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/parse.h>
#include <gg/hytxt.h>

/* #define PARSER_DEBUG */

/* ------------------------------------------------------------------------ */
struct TEXT_SEGMENT *hyx_parser_finish_segment (
struct HYX_PARSER_STATUS *lps)
{
  struct TEXT_SEGMENT *seg= (struct TEXT_SEGMENT *) 0;
  struct TEXT_ELEMENT *tt=  (struct TEXT_ELEMENT *) 0;

  if (lps == (struct HYX_PARSER_STATUS *) 0)
    return (struct TEXT_SEGMENT *) 0;

  if ((seg= hyx_mktx_segm (lps->HPS_segment, lps->HPS_segment_length))
      != (struct TEXT_SEGMENT *) 0)
  {
#ifdef PARSER_DEBUG
    printf ("flushing 1 text segment\n");
#endif /* PARSER_DEBUG */

    if (!lps->HPS_text_alloc_flag)
    {
#ifdef PARSER_DEBUG
      printf ("flushing 2 text element\n");
#endif /* PARSER_DEBUG */

      /* create new text element node and add it to the context */
      *lps->HPS_ptx= tt=
        hyx_mktx_elem (lps->HPS_parser_level, lps->HPS_element_type);

      lps->HPS_ptxs= &tt->TE_text_segment;
      lps->HPS_ptx= &tt->TE_next;
      lps->HPS_tx_cnt++;
      lps->HPS_text_alloc_flag= 1;
/* printf ("tt->TE_type=%d\n", tt->TE_type); */
    }

    *lps->HPS_ptxs= seg;
    lps->HPS_ptxs= &seg->TSEG_next;
    lps->HPS_tx_cnt++;

#ifdef PARSER_DEBUG
    diag_display_text_element (stdout, tt, (char *) 0);
    fputc ('\n', stdout);
#endif /* PARSER_DEBUG */
  }

  lps->HPS_segment_length= 0;
  lps->HPS_tx_last= tt;

  return seg;
}

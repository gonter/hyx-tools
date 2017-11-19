/*
 *  FILE %ds/hyxp/hyxp0003.c
 *
 *  read one lexicon entry
 *
 *  written:       1995-07-04
 *                 1996-02-18 12:29:27
 *  latest update: 2001-02-18 18:55:17
 *  $Id: hyxp0003.c,v 1.5 2004/05/08 15:40:19 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int hyx_parse2_char (
struct HYX_PARSER_STATUS *hps,
struct TEXT_ELEMENT **le,       /* datastructure to be built                */
int ch,                         /* character to be processed                */
long end_tags [],               /* set of possible end tags                 */
int end_tag_count)              /* number of possible endtags               */
{
  struct HYX_PARSER_CLASS *hpc;
  struct TEXT_ELEMENT *tt;      /* read tagging text                        */
  long t_id;                    /* tag id of the read taggin text           */
  int i;                        /* end tag index                            */

  if ((tt= hyx_parse_char (hps, ch)) != (struct TEXT_ELEMENT *) 0)
  {
    hpc= hps->HPS_hpc;
#ifdef PARSER_DEBUG
printf ("hyxp0003: po_id_tag=%d po_strip=%d\n",
  hpc->HPC_po_id_tag, hpc->HPC_po_strip);
#endif

    if (hpc->HPC_po_strip) hyx_strip_text_elem (tt);

    if (hpc->HPC_po_id_tag
        && (t_id= hyx_get_tag_definition (hpc, tt, 1)) > 0L
       )
    {
      for (i= 0; i < end_tag_count; i++)
        if (t_id == end_tags [i])
        {
          *le= hyx_parser_get_text_list (hps);
          return 1;       /* there's nothing else to read for now ... */
        }
    }
  }

  if (ch == -1)
  {
    *le= hyx_parser_get_text_list (hps);
    return 1;
  }

  return 0;
}

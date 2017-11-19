/*
 *  FILE %usr/lexicon/dictadd8.c
 *
 *  written:       1991 04 12
 *                 1995-08-23
 *  latest update: 2001-02-18 19:26:18
 *  $Id: dictadd8.c,v 1.2 2001/02/19 00:27:17 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_purge_entry (
struct TEXT_ELEMENT **tx_list,
long purge_tags [],
int purge_tags_flags [],
int purge_tags_cnt)
{
  long last_tag_id= -1L;
  struct TEXT_ELEMENT **tx, *t;
  struct TAG_DEFINITION *td;
  int purge_text= 0;
  int i;

  if (tx_list == (struct TEXT_ELEMENT **) 0) return -1;

  for (tx= tx_list;; tx= &(*tx)->TE_next)
  {
ONCE_MORE:
    if ((t= *tx) == (struct TEXT_ELEMENT *) 0) break;
    switch ((int) t->TE_level)
    {
      case 0: /* moeglicherweise getaggter Text */
        if (last_tag_id != -1L && purge_text) goto DISCARD;
        last_tag_id= -1L;
        break;

      case 1: /* Tag */
        td= t->TE_tag_definition;
        last_tag_id= (td == (struct TAG_DEFINITION *) 0) ? -1L : td->tag_id;
        purge_text= 0;
        for (i= 0; i < purge_tags_cnt; i++)
          if (last_tag_id == purge_tags [i])
          {
            purge_text= purge_tags_flags [i];
            goto DISCARD;
          }
        break;

      default:  /* anderer Tag-Level; z.B: <<xyz>>      */
                /* kommt in den Muell                   */
DISCARD:
        *tx= t->TE_next;
        t->TE_next= (struct TEXT_ELEMENT *) 0;
        hyx_frtx_elem_list (t);
        goto ONCE_MORE;
    }
  }

  return 0;
}

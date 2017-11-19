/*
 *  FILE ~/usr/ds/hyxp/hyxp0012.c
 *
 *  written:       1991 03 18
 *                 1995-03-30: moved to %ds/hyxp
 *  latest update: 1995-08-19
 *
 */

#include <stdlib.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long _hyx_text_freed= 0L;
long _hyx_markup_freed= 0L;

/* ------------------------------------------------------------------------ */
int hyx_frtx_elem_list (struct TEXT_ELEMENT *t1)
{
  struct TEXT_ELEMENT *t2;
  struct MARKUP *m;

  while (t1 != (struct TEXT_ELEMENT *) 0)
  {
    t2= t1->TE_next;

    if (--(t1->TE_link_count) <= 0)
    {
      if (t1->sig == SIG_TEXT_ELEMENT)
      {
        hyx_frtx_segm_list (t1->TE_text_segment);
        _hyx_text_freed++;
      }
      else
      if (t1->sig == SIG_MARKUP)
      {
        m= (struct MARKUP *) t1;
        hyx_frtx_elem_list (m->tag_open);
        hyx_frtx_elem_list (m->tagged_text);
        hyx_frtx_elem_list (m->tag_close);
        _hyx_markup_freed++;
      }
      free (t1);
    }
    t1= t2;
  }

  return 0;
}

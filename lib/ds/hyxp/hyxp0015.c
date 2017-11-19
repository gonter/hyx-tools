/*
 *  FILE %ds/hyxp/hyxp0015.c
 *
 *  Text Node und Text Segment Erzeugen
 *
 *  written:       1991 03 28
 *  latest update: 1996-02-18 12:07:22
 *  $Id: hyxp0015.c,v 1.3 2004/05/08 15:40:21 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long _hyx_markup_allocated= 0L;  /* T2D: -> HYX_PARSER_CLASS */

/* ------------------------------------------------------------------------ */
struct MARKUP *hyx_make_markup (
struct HYX_PARSER_CLASS *hpc,
void *start_tag,                /* Stop Tag; String oder Struktur           */
void *marked_text,              /* Markup Text; String oder Struktur        */
void *stop_tag,                 /* Stop Tag; String oder Struktur           */
struct TAG_DEFINITION *tag_def, /* moegliche Tag Defintion fuer Markup      */
int flags)                      /* Bit 0: Start Tag als Struktur            */
                                /* Bit 1: Markup Text als Struktur          */
                                /* Bit 2: Stop Tag als Struktur             */
{
  struct MARKUP *m;
  struct TEXT_ELEMENT *t;
  struct TAG_DEFINITION *td= (void *) 0;

  if ((m= hyx_new_markup ()) == (struct MARKUP *) 0)
    return (struct MARKUP *) 0;

  _hyx_markup_allocated++;
  m->sig= SIG_MARKUP;

  if (start_tag != (void *) 0)
  {
    m->tag_open= t= (flags & 0x0001)
      ? (struct TEXT_ELEMENT *) start_tag
      : hyx_mktx_elem_and_segm (hpc, (char *) start_tag,
                               (long) strlen ((char *) start_tag),
                               1L, TEt_tag, 1, 1);
    if (t != (void *) 0) td = t->TE_tag_definition;
  }

  if (marked_text != (void *) 0)
  {
    m->tagged_text = (flags & 0x0002)
      ? (struct TEXT_ELEMENT *) marked_text
      : hyx_mktx_elem_and_segm (hpc, (char *) marked_text,
                               (long) strlen ((char *) marked_text),
                               0L, TEt_text, 0, 0);
  }

  if (stop_tag != (void *) 0)
  {
    m->tag_open = (flags & 0x0004)
      ? (struct TEXT_ELEMENT *) stop_tag
      : hyx_mktx_elem_and_segm (hpc, (char *) stop_tag,
                               (long) strlen ((char *) stop_tag),
                               1L, TEt_tag, 1, 1);
  }

  m->tag_definition= (tag_def != (struct TAG_DEFINITION *) 0)
                     ? tag_def : td;

  return m;
}

/*
 *  FILE %ds/hyxp/hyxp0011.c
 *
 *  Text Node und Text Segment Erzeugen
 *
 *  written:       1991 03 27
 *  latest update: 2001-02-18 18:16:58
 *  $Id: hyxp0011.c,v 1.3 2003/06/25 10:11:56 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_mktx_elem_and_segm (
struct HYX_PARSER_CLASS *hpc,
char *str,
long lng,
long level,
int typ,
int get_tag_def,
int append)
{
  struct TEXT_ELEMENT *t;
  struct TEXT_SEGMENT *ts;
  int l;

/** printf ("hyxp0011: str='%s', lng=%ld, level=%ld\n", str, lng, level); **/

  if (str == (char *) 0 || *str == 0
      || (ts= hyx_mktx_segm (str, lng)) == (struct TEXT_SEGMENT *) 0
      || (t= hyx_mktx_elem (level, typ)) == (struct TEXT_ELEMENT *) 0
     )
    return (struct TEXT_ELEMENT *) 0;

  t->TE_text_segment= ts;

  if (get_tag_def && level == 1L)
  {
    char *name;

    for (l= 0; str [l]; l++)
    {
      if (str [l] == ' '
          || str [l] == '\t'
          || str [l] == 0x0D
          || str [l] == 0x0A
         ) break;
    }

    t->TE_tag_name= name= strndup (str, l);
    t->TE_tag_definition= hyx_identify_tag (hpc, name, append);
  }

  return t;
}

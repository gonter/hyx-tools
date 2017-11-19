/*
 *  FILE %ds/hyxp/hyxp0014.c
 *
 *  remove white space characters at the beginning and end
 *  of a text segment and excessive white spaces inbetween
 *  a text segment.
 *
 *  written:       1991 03 27
 *                 1995-03-30: moved to %ds/hyxp
 *  latest update: 1996-02-11 12:53:47
 *  $Id: hyxp0014.c,v 1.2 2003/06/25 10:11:56 gonter Exp $
 *
 */

#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
extern long _hyx_txsegm_free_size;

/* ------------------------------------------------------------------------ */
int hyx_strip_text_elem (struct TEXT_ELEMENT *t)
{
  struct TEXT_SEGMENT *ts1;
  struct TEXT_SEGMENT *ts2;
  char *cp1;
  char *cp2;
  long lng1;
  long lng2;
  int status= 0;
  long discarded= 0L;

  ts1=    t->TE_text_segment;
  cp1=  ts1->TSEG_text_array;
  lng1= ts1->TSEG_text_lng;
  ts2=    t->TE_text_segment;
  cp2=  ts2->TSEG_text_array;
  lng2= ts2->TSEG_text_lng;

  while (ts1 != (struct TEXT_SEGMENT *) 0)
  {
    if (lng1 == 0L)
    {
      if ((ts1= ts1->TSEG_next) == (struct TEXT_SEGMENT *) 0)
      {
        if (ts2 != (struct TEXT_SEGMENT *) 0 && discarded > 0L)
        {
          ts2->TSEG_text_lng -= discarded;
          hyx_frtx_segm_list (ts2->TSEG_next);
        }
        break;
      }
      cp1= ts1->TSEG_text_array;
      lng1= ts1->TSEG_text_lng;
    }

XXX:
    if (lng2 == 0L)
    {
      if ((ts2= ts2->TSEG_next) == (struct TEXT_SEGMENT *) 0)
        break; /* Fehler!! */
      cp1= ts2->TSEG_text_array;
      lng1= ts2->TSEG_text_lng;
    }

    switch (status)
    {
      case 0:
        switch (*cp1 & 0x00FF)
        {
          case 0x20: case 0x09:
          case 0x0A: case 0x0D:
            discarded++;
            break;
          default:
            *cp2++ = *cp1;
            lng2--;
            status= 1;
            break;
        }
        break;
      case 1:
        switch (*cp1 & 0x00FF)
        {
          case 0x20: case 0x09:
          case 0x0A: case 0x0D:
            status= 2;
            discarded++;
            break;
          default:
            *cp2++= *cp1;
            lng2--;
            break;
        }
        break;
      case 2:
        switch (*cp1 & 0x00FF)
        {
          case 0x20: case 0x09:
          case 0x0A: case 0x0D:
            discarded++;
            break;
          default:
            *cp2++= ' ';
            lng2--;
            discarded--;
            status= 1;
            goto XXX;   /* character einsetzen */
        }
        break;
    }
    cp1++;
    lng1--;
  }

  _hyx_txsegm_free_size += discarded;

  return (status == 0) ? 1 : 0;
}

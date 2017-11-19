/*
 *  FILE ~/usr/ds/hyxp/hyxp0017.c
 *
 *  Text Segment in ein Character Array uebertragen
 *
 *  written:       1991 03 18
 *  latest update: 1995-03-30
 *
 */

#include <memory.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int hyx_copy_tx_segm_list (char *dest, int size, struct TEXT_SEGMENT *ts)
/* Return: Zahl der kopierten Zeichen */
{
  int cnt= 0;
  int lng;

  if (dest == (char *) 0
     || --size <= 0) return -1; /* Fehler; ueberhaupt kein Platz vorhanden  */
                                /* Platz fuer abschliessende Null vorsehen  */

  while (ts != (struct TEXT_SEGMENT *) 0)
  {
    lng= (int) ts->TSEG_text_lng;
    if (size < lng)
    { /* aktuelles Textsegment geht sich nicht mehr ganz aus ... */
      memcpy (dest, ts->TSEG_text_array, size);
      dest [size]= 0;
      return cnt + size;
    }

    memcpy (dest, ts->TSEG_text_array, lng);
    cnt  += lng;
    size -= lng;
    dest [lng]= 0;
    dest= &dest[lng];
    ts= ts->TSEG_next;
  }

  return cnt;
}

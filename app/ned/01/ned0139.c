/*
 *  FILE %ned/01/ned0139.c
 *
 *  Speicherverwaltung: Anpassung von Text Segmenten
 *
 *  Anmerkung: wenn llng == 0, dann wird die Text Segment Liste
 *             geloescht.  Es ist also moeglich, dass Zeilen
 *             ohne Text Segmentliste existieren!
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1995-11-12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void txt_adj (
int llng,                       /* ... aktuelle Laenge anpassen             */
register struct TXT **tp)       /* Textsegmentliste auf ...                 */
                                /* ggf. verlaengern oder verkuerzen         */
{
  for (;;)
  {
    if (llng <= 0)
    {
      if (*tp != (struct TXT *) 0)
      {
        tx_free (*tp);
        *tp= (struct TXT *) 0;
      }
      return;
    }

    if (*tp == (struct TXT *) 0)
#ifndef ADVANCED_VERSION
    {
       if ((*tp= txch_alloc (TXT_LNG, 0x20)) == (struct TXT *) 0) return;
    }
#else
    {
      int xlng;

      xlng= (llng > 256) ? 256 : (((llng + 20) & 0x7FF8) + 5); /* ######## */
      if ((*tp= txch_alloc (xlng, 0x20)) == (struct TXT *) 0) return;

      /* ANM: Es werden Blocks der Groesse k*16+11 =< 256 allociert,        */
      /*      sodass zusammen mit den 4 Byte fuer den Link und              */
      /*      1 Byte Laengencode immer ein vielfaches eines                 */
      /*      Paragraphs angefordert wird.                                  */

      /* ANM: Dieser Funktionsteil darf erst aktiviert werdern, wenn        */
      /*      alle anderen Funktionen auch mit Text Segmenten mit           */
      /*      einer anderen Laenge als TXT_LNG operieren koennen.           */
    }
#endif
    llng -= (*tp)->t_lng;
    tp = &((*tp)->next);
  }
}

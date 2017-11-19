/*
 *  FILE %ds/ytree/yt_00004.c
 *
 *  ytree_lookup_word: Wort in YTREE Struktur suchen
 *
 *  written:       1991 04 14: aus nl_00006.c abgeleitet
 *  latest update: 1998-08-07 14:17:34
 *
 */

/* # define DEBUG_001 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/ytree.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
static struct YTREE *last_yt= (struct YTREE *) 0;
static int total_match_lng= 0;

/* ------------------------------------------------------------------------ */
struct YTREE *ytree_lookup_word (
struct YTREE *yp,               /* Wurzel des YTREEs                        */
unsigned char *wort)            /* zu suchendes Wort                        */
/* Return: Knoten, der die Info-Komponente des Worts enthaelt               */
/*         (struct YTREE *) 0 ... nicht gefunden                            */
{
  int ml;                       /* match length                             */

  total_match_lng= 0;
  last_yt= (struct YTREE *) 0;

  if (wort == (unsigned char *) 0) return (struct YTREE *) 0;

  while (yp != (struct YTREE *) 0
         && yp->YT_str[0] <= *wort)     /* lexicographische Sortierung      */
  {
    if ((ml= match_lng ((char *) yp->YT_str,
                        (char *) wort, yp->YT_lng_str)) > 0)
    {
      if (ml == strlen ((char *) wort) && ml == yp->YT_lng_str) return yp;

      if (ml == yp->YT_lng_str)
      { /* Textsegment kommt auch in str vor und  */
        /* Wort ist laenger als das Textsegment   */
        /* z.B. yp->YTstr  = 'AB'                 */
        /*      wort       = 'ABCD'               */
        /*      -> ml = 2                         */
        total_match_lng += ml;
        last_yt= yp;
        wort= &wort [ml];
        yp= yp->YT_down;
      }
      else return (struct YTREE *) 0;
    }
    else yp= yp->YT_next;
  }

  return (struct YTREE *) 0;
}

/* ------------------------------------------------------------------------ */
struct YTREE *ytree_lookup_word_get_last ()
{
  return last_yt;
}

/* ------------------------------------------------------------------------ */
int ytree_lookup_word_get_lng ()
{
  return total_match_lng;
}

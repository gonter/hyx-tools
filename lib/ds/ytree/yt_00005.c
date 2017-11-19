/*
 *  FILE %ds/ytree/yt_00005.c
 *
 *  ytree_delete_word: Wort-Eintrag aus YTREE entfernen
 *
 *  written:       1990 06 08
 *  latest update: 1996-01-21 23:34:00
 *
 */

/* #define DEBUG_001 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
#ifdef DEBUG_001
static V [10][64];
static int idx= 0;
static char *PI (struct YTREE *s)
{
  int i;

  i= idx++;
  if (idx >= 10) idx=0;
  strncpy ((char *) V [i], s->YT_str, s->YT_lng_str);
  ((char *)V[i])[s->YT_lng_str] = 0;
  return (char *) V[i];
}
#endif

/* ------------------------------------------------------------------------ */
int ytree_delete_word (
struct YTREE **ypp,             /* Wurzel des bearbeiteten YTREEs           */
unsigned char *wort)            /* zu loeschendes Wort                      */
/* Return: <0 .. Error */
{
  struct YTREE *tmp;
  struct YTREE *yp;             /* yp= *ypp */
  int ml;

#ifdef DEBUG_001
    char *PI();
    printf ("@61 YT_score_word *ypp=%08lX wort='%s'\n", *ypp, wort);
#endif

  if (ypp == (void *) 0) return -1; /* ERROR: YTREE empty */

CHECK:
  if (*ypp == (struct YTREE *) 0
      || (*ypp)->YT_str [0] > *wort)    /* lexicographische sortierung      */
  { /* wort existiert nicht im YTREE, falls dieser richtig                  */
    /* sortiert war; --> also ist alles bestens :-)                         */
#ifdef DEBUG_001
      printf ("@62 Wort '%s' nicht im YTREE vorhanden\n", wort);
#endif
    return 0;
  }

  yp= *ypp;
#ifdef DEBUG_001
    printf ("@62a Compare: '%s' '%s' -> ml=%d\n", PI(yp), wort,
            match_lng (yp->YT_str, wort, yp->YT_lng_str));
#endif

  if ((ml= match_lng ((char *) yp->YT_str, (char *) wort, yp->YT_lng_str)) > 0)
  {
    if (ml == strlen ((char *) wort) && ml == yp->YT_lng_str)
    { /* exakter Match */
#ifdef DEBUG_001
        printf ("@63 Exakter Match: '%s'\n", wort);
#endif
      /* ypp zeigt auf den Pointer, der die Adresse des Knoten enthaelt,    */
      /* der das Wort-Ende des gesuchten Wortes darstellt.                  */
      /* Wenn dort das EOW-Flag nicht gesetzt ist, dann ist das Wort        */
      /* eigentlich gar nicht gespeichert. (Dieser Fall muss nicht extra    */
      /* behandelt werden, da er bei den anderen Faellen abgedeckt wird.    */
      /* if (yp->YT_flags & YFflag_EOW) return 0;                           */
      /* Sonst kann man 3 Faelle unterscheiden:                             */
      /* Fall A: es gibt KEINE Worte, die noch weitergehen.                 */
      /* Fall B: es gibt EIN Wort, das noch weitergeht.                     */
      /* Fall C: es gibt MEHRERE Worte, die noch weitergehen.               */
      if (yp->YT_down == (struct YTREE *) 0)
      { /* *** FALL A *** */
        *ypp= yp->YT_next;
        free (yp);
        return 0;
      }
      else
      {
        if (yp->YT_down->YT_next == (struct YTREE *) 0)
        { /* *** FALL B *** zwei Knoten joinen */
          tmp= ytree_alloc (yp->YT_str,
                            yp->YT_lng_str + yp->YT_down->YT_lng_str);
          memcpy ((&tmp->YT_str [yp->YT_lng_str]),
                  yp->YT_down->YT_str,
                  yp->YT_down->YT_lng_str);
          tmp->YT_down=  yp->YT_down->YT_down;
          tmp->YT_flags= yp->YT_down->YT_flags;
          tmp->YT_info=  yp->YT_down->YT_info;
          tmp->YT_next=  yp->YT_next;
          *ypp= tmp;
          free (yp->YT_down);
          free (yp);
          return 0;
        }
        else
        { /* *** FALL C *** */
          yp->YT_flags= 0; /* ###################### */
          yp->YT_info= 0L;
        }
      }
      
    }

    if (ml == yp->YT_lng_str)
    { /* Textsegment kommt auch in str vor und  */
      /* Wort ist laenger als das Textsegment    */
      /* z.B. yp->YTstr  = 'AB'                 */
      /*      wort       = 'ABCD'               */
      /*      -> ml = 2                         */
#ifdef DEBUG_001
        printf ("@64 Textsegment '%s' auch in '%s'\n", PI(yp), wort);
#endif
      wort= &wort [ml];
      ypp= &yp->YT_down;
      goto CHECK;
    }
    fprintf (stderr, "yt_00005.c(136) internal error!\n");
    return -1;
  }
  else
  { /* kein Match */
#ifdef DEBUG_001
      printf ("@67 Kein Match: '%s' wort='%s'\n", PI(yp), wort);
#endif
    ypp= &yp->YT_next;
    goto CHECK;
  }

  fprintf (stderr, "yt_00005.c(148) internal error!\n");
  return -1;
}

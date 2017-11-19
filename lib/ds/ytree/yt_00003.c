/*
 *  FILE %ds/ytree/yt_00003.c
 *
 *  ytree_insert_word: YTREE Struktur aufbauen
 *
 *  written:       1990 06 02
 *                 1991 03 16: Revision; AIX
 *  latest update: 1995-12-30
 *  $Id: yt_00003.c,v 1.3 2002/10/16 04:44:51 gonter Exp $
 *
 */

/* #define DEBUG_001 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/ytree.h>
#include <gg/strings.h>

long YTREE_truncated= 0L;       /* number of bytes used up by node splits   */

#ifdef DEBUG_001
static char *PI (struct YTREE *s);
#endif

/* ------------------------------------------------------------------------ */
struct YTREE  *ytree_insert_word (
struct YTREE **ypp,             /* Wurzel des erzeugten YTREEs              */
unsigned char *key)             /* einzusortierendes Wort                   */
/* Return: Knoten, der die Info-Komponente des Worts enthaelt               */
{
  struct YTREE *new_node;       /* neu angelegter Knoten                    */
  struct YTREE *next_node;      /* neu angelegter nachfolgender Knoten      */
  struct YTREE *yp;             /* yp= *ypp                                 */
  int ml;                       /* match length                             */
  int lng_str;                  /* length of string segment in current node */

#ifdef DEBUG_001
  printf ("@61 YT_score_word *ypp=%08lX key='%s'\n", *ypp, key);
#endif

  if (ypp == (struct YTREE **) 0
      || key == (unsigned char *) 0
     )
    return (struct YTREE *) 0; /* ERROR */

CHECK:
  if (*ypp == (struct YTREE *) 0
      || (*ypp)->YT_str[0] > *key       /* lexicographische Sortierung      */
     )
  { /* key als neuen Knoten anlegen */
#ifdef DEBUG_001
    printf ("@62 Wort '%s' als neuen Knoten anlegen\n", key);
#endif

    if ((new_node= ytree_alloc (key, -1)) == (struct YTREE *) 0)
      return (struct YTREE *) 0;

    new_node->YT_next= *ypp;
    *ypp= new_node;

    return new_node;
  }

  yp= *ypp;
  lng_str= yp->YT_lng_str;

#ifdef DEBUG_001
  printf ("@62a Compare: '%s' '%s' -> ml=%d\n", PI(yp), key,
          match_lng (yp->YT_str, key, lng_str));
#endif

  if ((ml= match_lng ((char *) yp->YT_str, (char *) key, lng_str)) > 0)
  {
    if (ml == strlen ((char *) key) && ml == lng_str)
    { /* exakter Match */
#ifdef DEBUG_001
      printf ("@63 Exakter Match: '%s'\n", key);
#endif
      return yp;
    }

    if (ml == lng_str)
    { /* Textsegment kommt auch in str vor und Wort ist laenger als         */
      /* das betrachtete Textsegment => Baum weiter absteigen               */
      /* z.B. yp->YT_str = 'AB'                 */
      /*      key        = 'ABCD'               */
      /*      -> ml = 2                         */
#ifdef DEBUG_001
      printf ("@64 Textsegment '%s' auch in '%s'\n", PI(yp), key);
#endif

      key= &key [ml];
      ypp= &yp->YT_down;

      goto CHECK;
    }

    /* sonst split nach match_lng: ---------------------------- */
    /* Hier koennen bei gegebener ml folgende Faelle auftreten: */
    /* 1.  yp->YT_str = 'ABDC'  |                               */
    /*     key        = 'ABCD'  |                               */
    /*     -> ml = 2            |  --> Split 1                  */
    /* 2.  yp->YT_str = 'ABCD'  |                               */
    /*     key        = 'ABDC'  |                               */
    /*     -> ml = 2            |  --> Split 2                  */
    /* 3.  yp->YT_str = 'ABCD'  |                               */
    /*     key        = 'AB'    |                               */
    /*     -> ml = 2            |  --> Split 2 verkuerzt        */
    if (strlen ((char *) key) > ml && yp->YT_str [ml] > key [ml])
    {
#ifdef DEBUG_001
      printf ("@65 Split1: '%s' key='%s' nach %d\n",
              PI(yp), key, ml);
#endif

      if ((new_node= ytree_alloc (&key [ml], -1)) == (struct YTREE *) 0
          || (new_node->YT_next= next_node=
               ytree_alloc (&yp->YT_str [ml], lng_str-ml))
             == (struct YTREE *) 0
         )
        return (struct YTREE *) 0;

      next_node->YT_down=       yp->YT_down;
      yp->YT_down=              new_node;
      YTREE_truncated +=        lng_str - ml;
      yp->YT_lng_str=           ml;
      next_node->YT_info=       yp->YT_info;
      next_node->YT_flags=      yp->YT_flags;
      yp->YT_info=              0L;
      yp->YT_flags=             0;

      ytree_repack (ypp);
      /* yp is now invalid!! */

      return new_node;
    }
    else
    {
#ifdef DEBUG_001
      printf ("@66 Split2: '%s' key='%s' nach\n",
              PI(yp), key, ml);
#endif

      if ((new_node= ytree_alloc (&yp->YT_str [ml], lng_str-ml))
          == (struct YTREE *) 0) return (struct YTREE *) 0;

      new_node->YT_down=        yp->YT_down;
      yp->YT_down=              new_node;
      YTREE_truncated +=        lng_str - ml;
      yp->YT_lng_str=           ml;
      new_node->YT_info=        yp->YT_info;
      new_node->YT_flags=       yp->YT_flags;
      yp->YT_info=              0L;
      yp->YT_flags=             0;

      ytree_repack (ypp);
      /* yp is now invalid!! */

      if (ml == strlen ((char *) key))
      { /* Neues Wort hat gleiche Laenge wie das bisherige Textsegment      */
        return *ypp; /* node was repacked!!! */
      }

      return new_node->YT_next= ytree_alloc (&key [ml], -1);
    }
  }
  else
  { /* kein Match */
#ifdef DEBUG_001
      printf ("@67 Kein Match: '%s' key='%s'\n", PI(yp), key);
#endif
    ypp= &yp->YT_next;

    goto CHECK;
  }
}

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

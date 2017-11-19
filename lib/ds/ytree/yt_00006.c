/*
 *  FILE %ds/ytree/yt_00006.c
 *
 *  Berechnung des Platzbedarfs eines YTREE-(Sub)-Trees
 *
 *  written:       1990 06 04
 *                 1991 03 16: Revision; AIX
 *  latest update: 1996-01-21 23:27:45
 *
 */

/* #define DEBUG_001 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
long ytree_size (struct YTREE *yt)
{
  long siz= 0;          /* Platzbedarf der Struktur             */
  long siz1;            /* Platzbedarf einer Sub-Struktur       */

  /********************************************************
  Entscheiden, ob eine Table erzeugt werden soll oder nicht
  ********************************************************/

  for (;
       yt != (struct YTREE *) 0;
       yt= yt->YT_next)
  {
#ifdef DEBUG_001
      printf ("-------- ytree_size \n");
      ytree_print_node (stdout, yt, 0);
#endif

    /* Platzbedarf fuer den Text-Teil und Info Komponente */
    siz1= ytree_size (yt->YT_down);

    siz1 += (long) yt->YT_lng_str;
    if (yt->YT_flags & YTflag_EOW)
    {
      if (yt->YT_down != (struct YTREE *) 0)
         siz1 += 2;     /* Wort Info muss uebersprungen werden koennen */

      siz1 += 5L;       /* 0-Code am Ende des Strings */
    }

    if (yt->YT_next != (struct YTREE *) 0)
    {
      /* ANM: am Ende der Liste darf kein Offset Code gespeichert werden */

      /* Platzbedarf fuer Offset Codes berechnen */
      if (siz1 < 0x100L)
      {
        siz1 += 2L;
        yt->YT_flags= (yt->YT_flags & YTflag_OFFx) | YTflag_OFF1;
      } else if (siz1 < 0x10000L)
      {
        siz1 += 3L;
        yt->YT_flags= (yt->YT_flags & YTflag_OFFx) | YTflag_OFF2;
      } else if (siz1 < 0x1000000L)
      {
        siz1 += 4L;
        yt->YT_flags= (yt->YT_flags & YTflag_OFFx) | YTflag_OFF3;
      } else
      {
        siz1 += 5L;
        yt->YT_flags= (yt->YT_flags & YTflag_OFFx) | YTflag_OFF4;
      }
    }

    yt->YT_size= siz1;
#ifdef DEBUG_001
    ytree_print_node (stdout, yt, 0);
#endif
    siz += siz1;
  }

  return siz;
}

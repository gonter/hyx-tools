/*
 *  FILE %ds/ytree/yt_00009.c
 *
 *  Ausgeben des YTREEs im LUT-Format
 *
 *  written:       1990 06 04
 *                 1991 03 15: Revision; AIX
 *  latest update: 1996-01-21 23:26:41
 *
 */

/* #define DEBUG_001 */
/* #define DEBUG_002 */        /* Vergleich mit dem ZTREE Verfahren */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
long ytree_dump (FILE *fo, struct YTREE *yt)
{
  long unique= 0;        /* Zahl der verschiedenen Eintraege */
  int i;
  char *cp;

  for (;
       yt != (struct YTREE *) 0;
       yt= yt->YT_next)
  {
    /* Offset Code ausgeben */
    if ((i= yt->YT_flags & YTflag_OFF) != 0)
    {
      i= i >> 4;
      fputc (i, fo);
      dpp_fwrite_long (fo, yt->YT_size-i-1, i);
    }

    cp= (char *) yt->YT_str;
    for (i= yt->YT_lng_str; i > 0; i--) fputc (*cp++, fo);

    if (yt->YT_flags & YTflag_EOW)      /* Ende eines Wortes */
    {
      if (yt->YT_down != (struct YTREE *) 0)
      { /* Sonderfall: bisheriger String ist einerseits selbst eine Wort    */
        /*             als auch Prefix eines anderen Wortes!                */
        /*        Bsp: abc ... Wort;   abcdef ... Wort                      */
        /*      daher: Wort Info muss uebersprungen werden koennen          */
        fputc (0x01, fo);               /* sonst: 0x01 0x05                 */
        fputc (0x05, fo);
      }

      unique++;
      fputc (0, fo);                    /* End-of-Word Code */
      dpp_fwrite_long (fo, yt->YT_info, 4);
    }
    unique += ytree_dump (fo, yt->YT_down);
  }

  return unique;
}

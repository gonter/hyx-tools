/*
 *  FILE %ds/ytree/yt_00010.c
 *
 *  LUT in YTREE einscannen;
 *  YTREE wird knotenweise aus der LUT aufgebaut.
 *
 *  Damned, damned, damned .... da ist ein Hund drinn!!!!!!
 *
 *  written:       1990 11 11: in Anlehnung an lut_dump in LUT_0004.C
 *                 1991 03 16: Revision; AIX
 *  latest update: 1993-07-24
 *  $Id: yt_00010.c,v 1.3 2003/06/25 14:38:29 gonter Exp $
 *
 */

/** #define DEBUG_003 **/

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
static unsigned char lut_word_buffer [4096];

#ifdef DEBUG_003
#define xxxerr stdout
static void cdecl dump_stack (int tos);
static void cdecl printf_wrd (int idx);
#else
#define xxxerr stderr
#endif

/* ------------------------------------------------------------------------ */
struct YT_STACK
{
  long offs;
  struct YTREE **yta;
} ;

# define YT_STACK_SIZE 48
struct YT_STACK yt_stack [YT_STACK_SIZE];

/* ------------------------------------------------------------------------ */
int ytree_scan (
FILE *lut,                      /* Look Up Table; binaer eroeffnet          */
struct YTREE **ytp)             /* erzeugter YTREE */
{
  int idx= 0;                   /* untersuchte Stelle im Key (Suchwort)     */
  struct YTREE *y;
  int tos= 0;
  int cp;
  long cp2, v;

#ifdef DEBUG_003
printf ("\n");
#endif
  for (;;)
  {
    cp=fgetc (lut) & 0x00FF;
    if (feof (lut)) break;
#ifdef DEBUG_003
    printf ("cp=0x%02X tos=%d ytp=%08lX *ytp=%08lX [tos]=%08lX idx=%d w=",
            cp, tos, (long) ytp, (long) *ytp,
            (long) ((tos) ? yt_stack[tos-1].yta : 0),
            idx);
    printf_wrd (idx);
    dump_stack (tos);
#endif

    switch (cp)
    {
      case  0: /* Wortende gefunden */
        if (idx == 0)
        {
          /* ERROR !!!!!, oder so... ???? */
          fprintf (xxxerr, "ytree_scan: %d empty node to create!!!\n", __LINE__);
          if (tos == 0) goto OVER;  /* Ende des Scan Bereichs */
          y= *(yt_stack [tos-1].yta);
        }
        else *ytp= y= ytree_alloc (lut_word_buffer, idx);

#ifdef DEBUG_003
        printf ("Alloc1: %08lX %d ", (long) y, idx);
        printf_wrd(idx);
#endif
        if (y == (void *) 0)
        {
          fprintf (xxxerr, "ytree_scan: out of memory!\n");
          goto OVER;
        }
        y->YT_info= dpp_fread_long (lut, 4);
        y->YT_flags |= YTflag_EOW;
        idx=0;

        if (tos==0) goto OVER;  /* Ende des Scan Bereichs */
        tos--;
        fseek (lut, yt_stack [tos].offs, 0);
        ytp= yt_stack [tos].yta;
        ytp= &(*ytp)->YT_next;
        break;

      default:
        lut_word_buffer [idx++] = (char) cp;
        break;

      /* Offset Codes */
      case  1:
      case  2:
      case  3:
      case  4:
        v= dpp_fread_long (lut, cp);
        cp2= ftell (lut) + v;
        if (tos >= YT_STACK_SIZE)
        {
          fprintf (xxxerr, "ytree_scan: internal stack overflow!\n");
          goto OVER;
        }
        yt_stack [tos].yta= ytp;
        yt_stack [tos].offs= cp2;
        tos++;
        if (idx)
        {
          *ytp= y= ytree_alloc (lut_word_buffer, idx);
#ifdef DEBUG_003
          printf ("Alloc2: %08lX %d ", (long) y, idx);
          printf_wrd(idx);
#endif
          if (y == (void *) 0)
          {
            fprintf (xxxerr, "ytree_scan: out of memory!\n");
            goto OVER;
          }
          ytp= &y->YT_down;
          idx= 0;
        }
        break;
    }
  }

OVER:
  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef DEBUG_003
static void printf_wrd (int idx)
{
  int i;

  for (i=0;i<idx;i++) fputc (lut_word_buffer [i], stdout);
  fputc ('\n', stdout);
}

static void dump_stack (int tos)
{
  for (tos--; tos >= 0; tos--)
  {
    printf ("[%2d] offs=%lX yta=%lX *yta=%lX\n",
            tos,
            yt_stack[tos].offs, 
            (long) yt_stack[tos].yta,
            (long) *(yt_stack[tos].yta));
  }
}
#endif

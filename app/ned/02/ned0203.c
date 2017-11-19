/*
 *  FILE %ned/02/ned0203.c
 *
 *  display one line
 *  - TK_VERSION
 *
 *  written:       1987 04 08
 *                 1991 05 26: Revision
 *                 1991 07 04: Vollstaendige Ueberarbeitung, BLIT Puffer
 *  latest update: 1999-07-17 19:35:39
 *  $Id: ned0203.c,v 1.4 2005/06/14 02:36:06 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>

#ifdef USE_TK
#include <tcl.h>
#include <tk.h>
#include "edtcl.h"
#include "edtk.h"
#endif /* USE_TK */

#include "proto.h"

extern int CHR_FILLER;
extern int CHR_TAB_FILLER;
extern int DISPLAY_TABS;
extern int akt_page;
extern int blk, block_mode;
extern int COL_BLOCK, COL_FEATURE;
extern int ned_tabsize;
extern struct MARKER b_beg, b_end;

#ifndef USE_TK
/* #define VERSION_OLD_001 */
#endif
#define NEW_VERSION

#ifdef _AIX
#define __FLIP_FILLER
#endif /* _AIX */

#ifdef __hpux
#define __FLIP_FILLER
#endif /* _AIX */

#ifdef __SINIX__
#define __FLIP_FILLER
#endif

/* ------------------------------------------------------------------------ */
#ifdef NEW_VERSION

#ifdef MSDOS
#define BLIT_LINE_SIZE  134             /* maximum line length to use */
#else
#define BLIT_LINE_SIZE  1024
#endif
#define BLIT_LINE_LNG   2*BLIT_LINE_SIZE

static char blit_line [BLIT_LINE_LNG];  /* Struktur: (char,colour) *134     */

#ifdef USE_TK
/* BUG HERE */
#define MAX_GCS 128
static GC GC_table [MAX_GCS];           /* table of different GCs           */
static int GC_table_size;               /* number of different GCs          */
static int GC_index [BLIT_LINE_LNG];    /* GC idx table for each char pos   */
#endif /* USE_TK */

/* ------------------------------------------------------------------------ */
#ifdef USE_TK
int place_GC (GC gc)
{
  if (GC_table_size >= MAX_GCS) return -1;

  GC_table [GC_table_size]= gc;
  return GC_table_size++;
}
#endif /* USE_TK */

/* ------------------------------------------------------------------------ */
/* This function is used to display one horizontal region within a line.    */
/* The region may extend from the left edge to the right edge of the        */
/* window, however, it is also possible to display just a smaller portion   */
/* in response to a exposure event or something similar.                    */
void wd_displine (
register struct WINDOWCTRL *w,  /* bearbeitetes Window                      */
register struct LINE *l_ptr,    /* Datenstruktur fuer eine Zeile            */
                                /* NOTE: NULL is a legal value !!!          */
int l_num,                      /* Line Number == Schirmzeile               */
int xa,                         /* horizontal region begin                  */
int xb)                         /* horizontal region end                    */
{
#ifdef USE_TK
  NED_Widget *nw;               /* widget to be drawn                       */
  Drawable da;                  /* pixel area in widget to be drawn         */
  Display *dpy;                 /* display control structure                */
  int y_pos;                    /* vertical string position in pixels       */
  int x_pos= 0;                 /* horizontal string position in pixels     */
  int x_width;                  /* width of a single character              */
  int *bip;                     /* pointer into GC_index                    */
#define CHAR_SKIP 1
#else
  short *bip;                   /* 16-bit string transfer buffer pointer    */
  int ap;
#define CHAR_SKIP 2
#endif /* !USE_TK */

  int i;
  int idx;                      /* index in character and GC buffer         */
  int colour;                   /* aktuelle Darstellungsfarbe               */
  register struct TXT *tx;      /* current text segment                     */
  register int ih;              /* Index im Text Segment                    */
  register int ti;              /* Index im Text Segment                    */
  int tlng;                     /* length of the current text segment       */
  int wx;                       /* number of chars in display region        */
  int ahx;                      /* region start position within the line    */
  int l_lng;                    /* full line length                         */
  int xblock_mode;              /* assumed block display mode               */
  struct FEATURE *p_ftr;        /* currently processed feature element      */
  char *cp;                     /* text segment pointer                     */
  char *bp;                     /* char-wise transfer buffer pointer        */
  int ch;                       /* character being examined                 */
  int f_pos;                    /* feature position                         */

  if (xa < w->ax) xa= 0;
  if (xb > w->bx) xb= w->bx;
  if (xa > xb) return;          /* actually, nothing to do ...              */
                                /* It's possible that xa == xb, e.g. for    */
                                /* redisplaying the character at cursor pos.*/
  wx= xb - xa + 1;
  ahx= w->hv + xa - w->ax;

#ifdef USE_TK
  if ((nw= w->wc_widget) == (NED_Widget *) 0
      || nw->ned_window != w    /* not linked, must be in error! */
     ) return;

  da= Tk_WindowId (nw->tkwin);
  dpy= nw->display;

  y_pos= l_num * nw->line_height + nw->char_ascent;
  x_width= nw->char_width;
  x_pos= xa * x_width;

  GC_table_size= 0;

  colour= place_GC ((l_ptr != (struct LINE *) 0
                      && (l_ptr->line_flg & LINE_HIDDEN)
                    )
                    ? nw->hiddenTextGC
                    : nw->normalTextGC);
  bip= GC_index;
#else /* ^ USE_TK ^ *** v !USE_TK v */
  ap= akt_page;
  /* Blit Puffer mit Colour Codes initialisieren */

  colour= (l_ptr != (struct LINE *) 0 && (l_ptr->line_flg & LINE_HIDDEN))
           ? 0x03 : w->attr_text; /* @@@ T2D */
#ifdef __FLIP_FILLER
  colour= (CHR_FILLER << 8) + colour;
#else
  colour= CHR_FILLER + (colour << 8);
#endif /* __FLIP_FILLER */

  bip= (short *) blit_line;
#endif /* !USE_TK */

  /* reset colour index buffer and text buffer */
  bp= blit_line;
  for (i= wx; i > 0; i--) *bp++= ' ';
  if (l_ptr == (struct LINE *) 0)
  {
    for (i= wx; i > 0; i--) *bip++= colour;
    goto REST;
  }

  if (blk && (l_ptr->line_flg & LINE_inBLOCK))
       if (block_mode == BLOCK_MODE_standard)
            if (b_beg.ptr == l_ptr)
                 if (b_end.ptr == l_ptr)
                      xblock_mode= 3;           /* block begins and ends... */
                 else xblock_mode= 4;           /* block begins here        */
            else if (b_end.ptr == l_ptr)
                      xblock_mode= 5;           /* block ends here          */
                 else xblock_mode= 2;           /* complete line in block   */
       else xblock_mode= block_mode;
  else xblock_mode= 0;

  if (xblock_mode == 2)         /* the complete line is part of a marked    */
  {                             /* block, so switch the text color to block */
                                /* color and proceed in standard line       */
                                /* display mode.                            */
#ifdef USE_TK
    colour= place_GC (ned_get_blk_GC (nw));
#else
    colour= 0x20 + (COL_BLOCK << 8);
#endif
    xblock_mode= 0;
  }

  /* Colour Attribute eines active markups checken      */
  /* T2D: @@@ not fully implemented                     */
  /* T2D: 2000-12-09 Core Dump in the next line! */
  if ((p_ftr= l_ptr->l_active_ftr) != (struct FEATURE *) 0
      && p_ftr->ftr_display_mode == FTR_display_region
      && p_ftr->ftr_colour < 0x0100
     )
  {
    xblock_mode= 0;
#ifdef USE_TK
    colour= place_GC (ned_tk_get_GC (nw, p_ftr->ftr_colour));
#else
    colour= 0x20 + (p_ftr->ftr_colour << 8);
#endif /* !USE_TK */
  }

  /* reset colour index buffer and text buffer */
  for (i= wx; i > 0; i--) *bip++= colour;

  if (xblock_mode)              /* marked block begins in just that line    */
  {
    int j;

#ifdef USE_TK
    colour= place_GC (ned_get_blk_GC (nw));
    bip= GC_index;
#else
    colour= 0x20 + (COL_BLOCK << 8);
    bip= (short *) blit_line;
#endif

    j= b_beg.offset - ahx;
    switch (xblock_mode)
    {
      case 3:
        if (j >= wx) goto NEXT1;
        i= b_end.offset - b_beg.offset;
        if (j < 0)
        {
          i += j;
          j= 0;
        }
        bip += j;
        break;
      case 4: /* block begins here */
        if (j < 0) j= 0; /* hmpf? */
        bip += j;
        i= wx - j;
        break;
      case 5: /* block ends here */
        i= b_end.offset - ahx;
        break;
    }

    if (i < 0) i= 0;
    if (i > wx) i= wx;
    for (; i > 0; i--) *bip++= colour;
  }

NEXT1:
  /* zuletzt Colour Attribute von Markups in der Zeile einsetzen */
  for (p_ftr  = l_ptr->ftr;
       p_ftr != (struct FEATURE *) 0;
       p_ftr  = p_ftr->ftr_next)
  {
    f_pos= p_ftr->ftr_pos;

    switch (p_ftr->ftr_display_mode)
    {
      case FTR_display_hide:
        continue;
      case FTR_display_region:
        i= wx - f_pos - ahx;
        break;
      case FTR_display_point:
        if ((i= p_ftr->ftr_replarray_size) <= 0) i= 1;
        break;
      case FTR_display_replarray:
        i= p_ftr->ftr_replarray_size;
        break;
    }

    /* if (i+f_pos > wx) i= wx - f_pos; ### HV !!! */

#ifdef USE_TK
    colour= place_GC (ned_tk_get_GC (nw, p_ftr->ftr_colour));
    idx= f_pos - ahx;

    for (; i > 0; i--, idx++) if (idx >= 0) GC_index [idx]= colour;

#else
    bp= &blit_line [(f_pos - ahx)*2 + 1];
    colour= p_ftr->ftr_colour;
    if (colour == 0x0100) colour= w->attr_text; else
    if (colour == 0x0200 || colour == 0x0000) colour= COL_FEATURE;
    for (; i > 0; i--, bp += 2) *bp= (char) colour;
#endif
  }

  /* Start des Textes suchen */
  if (l_ptr->lng == 0 || (tx= l_ptr->txt) == (struct TXT *) 0) goto REST;

  tlng= tx->t_lng;
  for (ti= ahx;;)
  {
    if (ti - tlng < 0) break;
    ti -= tlng;
    if ((tx= tx->next) == (struct TXT *) 0)
       goto REST; /* Fehler: zuwenige Textsegmente  */
    tlng= tx->t_lng;
  }

  ih= ahx;
  l_lng= l_ptr->lng;
  cp= &(tx->t [ti]);

  /* Character Codes in Puffer eintragen */
  bp= blit_line;
  i= wx;
  while (i-- > 0 && ih++ < l_lng)
  {
    ch= *cp++ & 0x00FF;

#ifdef __EXPERIMENTAL__ /* 1996-07-26  2:29:19 */
    if (ch == 0x09)
    {
      int num_tabs;

      num_tabs= ned_tabsize - (ahx % ned_tabsize);

      while (i-- > 0 && num_tabs-- > 0)
      {
        *bp= (char) CHR_TAB_FILLER;       /* character code     */
        bp += CHAR_SKIP;                  /* colour code ist ok */
        ahx++;
      }
    }
    else
#endif /* __EXPERIMENTAL__ 1996-07-26  2:29:19 */
    {
      *bp= (char) ch;                   /* character code     */
      bp += CHAR_SKIP;                  /* colour code ist ok */
      ahx++;
    }

    if (++ti >= tlng)
    {
      if ((tx= tx->next) == (struct TXT *) 0) break;
      tlng= tx->t_lng;
      ti= 0;
      cp= tx->t;
    }
  }

REST:
  /* Puffer auf den Schirm knallen */
#ifdef USE_TK
  for (i= 0; i < wx;)
  {
    int j;

    bp=  blit_line+i;
    bip= GC_index+i;
    colour= *bip;
    for (j= 0; i+j < wx; j++) if (colour != *bip++) break;

    XDrawImageString (dpy, da, GC_table [colour], x_pos, y_pos, bp, j);
    i += j;
    x_pos += x_width * j;
  }
#else
  w_blit_line (ap, xa, l_num, wx, blit_line);
#endif

  w->l_upd= 0;
}
#endif /* NEW_VERSION */

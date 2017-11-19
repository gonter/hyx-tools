/*
 *  FILE %ned/08/ned0823.c
 *
 *  read a feature string
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:32:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
#define MAX_LINE 1024           /* T2D: should be global constant           */
static char lin [MAX_LINE];

/* ------------------------------------------------------------------------ */
/* Feature Zeile bis an das Ende (inkl. CR) einlesen und verarbeiten */
int rd_ftr (
struct WINDOWCTRL *wc,          /* associated window                        */
struct LINE *lpt,               /* line where feature is attached to        */
FILE *ff,                       /* input stream stream from .ftr file       */
struct FEATURE **fp,            /* feature entry to be read                 */
int p,                          /* Column Position                          */
char *repl_array,               /* replacement array produced               */
int *repl_size,                 /* length of replacement text               */
int repl_max)                   /* size of replacement array                */
{
  struct FEATURE *f;            /* angelegtes Feature Record                */
  register struct TXT *tx=      /* Text Segment in der Zeile                */
              (struct TXT *) 0;
  struct LINE *lp;              /* Feature Line                             */
  int ftr_type= 0;              /* Feature Type                             */
  int tc;                       /* gelesenes Zeichen                        */
  int skip= 1;                  /* Blanks ueberspringen                     */
  int lin_idx= -1;              /* index into lin                           */

  fscanf (ff, "%d", &ftr_type);

  if (feof (ff)
      || (f= ned_new_feature (p, ftr_type)) == (struct FEATURE *) 0
     ) return -1;

  lp= f->ftr_text_line;

  /* Feature Text einlesen */
  for (;;)
  {
    tc= fgetc (ff) & 0x00FF;
    if (feof (ff) || tc == 0x0A) break;

    if (tc == 0x0D) continue;
    if (skip && tc == 0x0020) continue;
    skip= 0;

    if (lin_idx >= 0 && lin_idx < MAX_LINE) lin [lin_idx]= (char) tc;
    lin_idx++;

    if ((lp->lng % TXT_LNG) == 0)  /* Textsegment aufgebraucht */
    {
      if (lp->lng == 0)
      { /* 1. Textsegment           */
        lp->txt= tx= txch_alloc (TXT_LNG, 0x20);
      }
      else
      { /* weitere Textsegmente     */
        tx->next= txch_alloc (TXT_LNG, 0x20);
        tx= tx->next;
      }
    }

    if (tx == (struct TXT *) 0)
    { 
      ned_error_message (ERR_MEMORY);
      break;
    }
    tx->t [lp->lng % TXT_LNG] = (char) tc;
    lp->lng++;
  }

  if (lin_idx > 0) lin [lin_idx-1]= 0;

  ned_insert_feature (fp, f);

  ned_identify_feature (wc, lpt, p, ftr_type, f, lin,
                        repl_array, repl_size, repl_max);

  return 0;
}

/*
 *  FILE %ned/04/ned0402b.c
 *
 *  file I/O: load a file
 *
 *  written:       1987 04 08
 *                 1990 01 12: isolation
 *                 1991 02 03: revision
 *                 1991 09 18: use logic path names
 *                 1996-11-03: extracted from ned0402.c
 *  latest update: 1999-04-25 16:30:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/streams.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

extern int ned_tabsize;

#define repl_max 1024           /* T2D: constant sizes should be coordinated*/
static char repl_array [repl_max];

/* ------------------------------------------------------------------------ */
int ned_stream_read (
struct WINDOWCTRL *w,           /* betroffenes Window                       */
struct LINE **laptr,            /* ^ erste eingelesene Zeile                */
struct LINE **lzptr,            /* ^ letzte eingelesene Zeile               */
long lz_offset,                 /* end postition in the stream              */
int format,                     /* Default: ASCII Files einlesen            */
struct STREAM_OBJECT *so,       /* input stream                             */
FILE *ff,                       /* feature file                             */
int flcnt,                      /* line number for next feature             */
int fccnt)                      /* column number for next feature           */
{
  int tc;                       /* gelesenes Zeichen                        */
  int lcnt= 1;                  /* Zeilenezaehler im File                   */
  int ccnt= 0;                  /* column count im Binaer Modus             */

#ifdef EXPAND_TABS
  int tabcnt= 0;                /* > 0 -> ein vorgetaeuschtes Blank         */
#endif

  int feof_f= 0;                /* 1 -> EOF erreicht                        */
  int eoln;                     /* End-Of-Line Code bei Binaer Files        */
  int bin_x_llng;               /* Laenge von binaeren Zeilen               */
  int rc;                       /* Return Code von read SGML sequence       */
  int identify_eoln= 1;         /* Zustand des EOLN Identifiers             */
  int ignored_0x0D= 0;          /* 1 -> mindestens ein 0x0D ignoriert       */
                                /*      ##### dient fuer einen BUG-Fix #### */
  register struct LINE *lp;     /* currently processed line                 */
  register struct TXT *tx= (struct TXT *) 0;
  int repl_size= 0;             /* replace TAGs and Entities with text      */
  int repl_idx= 0;
  STREAM_next_char *_fgetc;
  STREAM_end *_feof;

  bin_x_llng= w->bin_llng;
  if ((eoln= w->bin_eoln) != 0x0A) identify_eoln= 0;

  *laptr= lp= alloc_line ();
  _fgetc= so->next_char;
  _feof= so->is_end;

  if (lp != (struct LINE *) 0)
     switch (format)
     {
       case FMT_BINARY: /* Binaer Modus: jedes Zeichen uninterpretiert      */
                        /* lesen und nach 70 Zeichen neue Zeile beginnen    */
         ccnt= 0;
         for (;;)
         {
           tc= (*_fgetc) (so);
           
           if ((*_feof) (so) || stream_position (so) >= lz_offset) feof_f= 1;
           ccnt++;

           if ((lp->lng) % TXT_LNG == 0)  /* Textsegment aufgebraucht         */
              if (lp->lng == 0)         /* 1. Textsegment                   */
                 lp->txt= tx= txch_alloc (TXT_LNG, 0x00);
              else
              {
                /* weitere Textsegmente */
                tx->next= txch_alloc (TXT_LNG, 0x00);
                tx= tx->next;
              }

           if (tx == (struct TXT *) 0)
           {
             *lzptr= lp;
             ned_error_message (ERR_MEMORY);
             break;
           }

           if (!feof_f)
           {
             tx->t [lp->lng % TXT_LNG]= (char) tc;
             lp->lng++;
           }

           if (ccnt >= bin_x_llng || (tc == eoln && eoln) || feof_f)
           {
             lcnt++;
             ccnt= 0;
             /* neue Zeile anhaengen */
             txt_adj (lp->lng, &lp->txt);
             *lzptr= lp;
             if (feof_f) break;

             if ((lp->next= alloc_line ()) == (struct LINE *) 0)
             {
               ned_error_message (ERR_MEMORY);
               break;
             }
             lp->next->prev= lp;
             lp= lp->next;
           }
         }
         break;

       case FMT_ASCII:
       case FMT_SGML:
         for (;;)
         {
NEXT_TRY:
           if (repl_size > 0)           /* insert characters from           */
           {                            /* the replacement array            */
             tc= repl_array [repl_idx++] & 0x00FF;
             if (repl_idx >= repl_size) repl_idx= repl_size= 0;
             goto INS_CHAR;
           }

           /* Features suchen und ggf einlesen */
           while (ff != (FILE *) 0 && flcnt && lcnt >= flcnt && ccnt >= fccnt)
           {
             rd_ftr (w, lp, ff, &lp->ftr, /* fccnt (1995-10-22) */ lp->lng,
                     repl_array, &repl_size, repl_max);
             fscanf (ff, "%d%d", &flcnt, &fccnt);
             if (feof (ff)) flcnt= 0;
             if (repl_size > 0)
             {
               repl_idx= 0;
               goto NEXT_TRY;
             }
           }

#ifdef EXPAND_TABS
           if (tabcnt > 0)
           {
             tc= 0x20;
             tabcnt--;
           }
           else
           {
             tc= (*_fgetc) (so);
             if ((*_feof) (so) || stream_position (so) >= lz_offset) feof_f= 1;
             ccnt++;
             if (tc == TAB_CHAR
                 && format == FMT_ASCII
                 /* && tab_expand << TAB ##### */
                )
             {
               tabcnt= ned_tabsize-1 - (lp->lng % ned_tabsize);
               tc= TAB_EXPN;           /* -> es verbleiben noch 0..7 Blanks */
             }
           }
#else
           tc= (*_fgetc) (so);
           if ((*_feof) (so) || stream_position (so) >= lz_offset) feof_f= 1;
           ccnt++;
#endif

           switch (identify_eoln)
           {
             case 1: /* first character is a Carriage Return */
               if (tc == 0x0D) identify_eoln= 2;
               break;
             case 2:
               if (tc == 0x0A)
               { /* if next character is a Line Feed, then      */
                 /* we have a MSDOS text file (CR-LF pairs)     */
                 identify_eoln= 0;
               }
               else
               { /* otherwise, this seems to be MAC where only  */
                 /* CR is used at end of lines                  */
                 eoln= w->bin_eoln= 0x0D;
                 lp->line_flg ^= LINE_CODE_0x0D;
                 identify_eoln= 3;
                 goto EOLN;
               }
               break;
           }

           if (tc == 0x0D && format != FMT_BINARY && tc != eoln)
           {
             lp->line_flg |= LINE_CODE_0x0D;
             ignored_0x0D= 1;
             continue;
           }

           if (tc == eoln                 /* normales Zeilenende            */
               || feof_f                  /* EOF => EOLN                    */
               || lp->lng >= LINE_LNG_TXT /* maximum line length reached    */
              )
           {
EOLN:
             lcnt++;
             ccnt= 0;
             /* neue Zeilensegment anhaengen */
             txt_adj (lp->lng, &lp->txt);
             *lzptr= lp;
             if (feof_f)
             {
               /* BUG FIX: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
               if (ignored_0x0D) lp->line_flg |= LINE_CODE_0x0D;
               /* wird gemacht, da bei MSDOS Files in der letzten   */
               /* Zeile aus unerfindlichen Gruenden das 0x0D Flag   */
               /* einfach 'liegenbleibt'... _______________________ */
               break;
             }

             if ((lp->next= alloc_line ()) == (struct LINE *) 0)
             {
               ned_error_message (ERR_MEMORY);
               break;
             }
             lp->next->prev= lp;
             lp= lp->next;
             if (identify_eoln == 3)
             { /* gerade gelesenes Zeichen muss noch verarbeitet werden     */
               identify_eoln= 0;
               goto CHAR;
             }
            }
           else
           {
CHAR:
             if (format == FMT_SGML)
             {
               switch (tc)
               {
                 case '<':
                   rc= rd_sgml_tag (w, lp, so, &lp->ftr, lp->lng,
                                    Ftype_SGML_TAG, '<', '>',
                                    repl_array, &repl_size, repl_max);
                   repl_idx= 0;
                   break;
                 case '&':
                   rc= rd_sgml_tag (w, lp, so, &lp->ftr, lp->lng,
                                    Ftype_SGML_ENTITY, '&', ';',
                                    repl_array, &repl_size, repl_max);
                   repl_idx= 0;
                   break;
                 default: goto INS_CHAR;
               }

               switch (rc)
               {
                 default:
                   ned_error_message (ERR_SGML_READ);
                   repl_size= 0;
                 case 0:
                 case 1:
                   goto NEXT_TRY;
               }
             }

#ifdef __JUNK__ /* 1996-03-16 10:04:34 */
#define __JUNK__ /* 1996-07-25 21:03:35 */
             if (tc == '\t') /* T2D: && show tabs */
             { /* display tabs as a series of chars */
               int tabcnt= 0;        /* > 0 -> ein vorgetaeuschtes Blank  */

               tabcnt= ned_tabsize-1 - (lp->lng % ned_tabsize);
               strcpy (repl_array, "________");
               repl_size= tabcnt;
               goto NEXT_TRY;
             }
#endif /* __JUNK__ 1996-03-16 10:04:34 */

INS_CHAR:
             if ((lp->lng%TXT_LNG) == 0)        /* Textsegment aufgebraucht */
                if (lp->lng == 0)               /* 1. Textsegment           */
                     lp->txt= tx= txch_alloc (TXT_LNG, 0x00);
                else
                {
                  /* weitere Textsegmente     */
                  tx->next= txch_alloc (TXT_LNG, 0x00);
                  tx= tx->next;
                }

             if (tx == (struct TXT *) 0)
             {
               *lzptr= lp;
               ned_error_message (ERR_MEMORY);
               break;
             }
             tx->t [lp->lng % TXT_LNG]= (char) tc;
             lp->lng++;
           }
         }
         break;
     }

  return 0;
}

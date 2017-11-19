/*
 *  include FILE <gg/ztree.h>
 *
 *  Anlegen des LUT-Woerterbuches mittels ZTREE Datenstruktur
 *
 *  written:       1989 03 29
 *                 1990 11 11: aus WORDCREA.H isoliert
 *  latest update: 1995-10-24
 *
 */

#ifndef __GG_ztree__
#define __GG_ztree__

#include <gg/floskel.h>

#ifndef ZTREE_DEPTH_MAX
#define ZTREE_DEPTH_MAX   100  /* max. Laenge eines Wortes,                 */
                               /* -> max. Tiefe des Woerterbuches           */
#endif

/* moegliche Informationen Åber ein Wort ----------------------------------- */
struct WORD_INFO
{
  int word_number;              /* Nummer des Wortes    */
  int word_frequency;           /* Haeufigkeit          */
} ;

/* ------------------------------------------------------------------------ */
struct ZTREE
{
  struct WORD_INFO wi;          /* moegliche Informationen zu einem Wort     */

  int next_char;
  int sub_cnt;                  /* fÅr die ganze Substruktur benoetigter     */
                                /* Platz im Binaerfile in Bytes              */
                                /* (Einschliesslich des Vater-Knotens?)     */
  struct ZTREE *next;           /* anderes Zeichen                          */
  struct ZTREE *sub;            /* dieses Zeichen; naechste Stelle           */
} ;

/* NL_00003.C ------------------------------------------------------------- */
int cdecl set_word_info (int code);

int cdecl score_word  (
struct ZTREE **pp1,     /* LEX-Baum                                     */
char *w,                /* gesuchtes Wort                               */
int   mode,             /* Bit 0 .. Zaehler auf diesen Wert setzen       */
                        /* Bit 1 .. Code in Word Number eintragen       */
int   cnt,              /* Zaehler um diesen Wert erhoehen                */
int   code)   ;         /* Word Number auf diesen Wert setzen           */
/* RETURN:  0 OK                */
/*         -1 Wort nicht ok     */
/*         -2 Out of Memory     */

int cdecl dump_lut (struct ZTREE *p1, FILE *fo);

#endif /* __GG_ztree__ */

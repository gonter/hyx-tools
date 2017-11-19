/*
 *  FILE ~/usr/ned/00/ned0001a.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe a (kein Praefix)
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include Files fuer
 *                             jede Praefix-Gruppe
 *  latest update: 2001-02-11 12:43:53
 *  $Id: ned0031a.c,v 1.2 2001/02/12 00:03:16 gonter Exp $
 *
 */

/* 0. normale Zeichen; keine Prefix-Codes - - - - - - - - - - - - - - - - - */
/* 00 */ xx,            /* Char  0x00:   Funktionstasten-PFX bei PC         */
/* 01 */ p_word_left,   /*         ^A:   Wort nach links                    */
/* 02 */ xx,            /*         ^B                                       */
/* 03 */ ned_page_down, /*         ^C:   Seite hinunter                     */
/* 04 */ ned_cursor_right,      /* ^D:   Cursor nach rechts                 */
/* 05 */ ned_cursor_up, /*         ^E:   Cursor hinauf                      */
/* 06 */ p_word_right_beg,      /* ^F:   Wort nach rechts                   */
/* 07 */ xx,            /*         ^G:   ein Zeichen rechts loeschen        */
/* 08 */ xx,            /* DEL     ^H:   ein Zeichen links  loeschen        */
/* 09 */ xx,            /* TAB     ^I:   Tabulator                          */
/* 0A */ p_ax_lng,      /*         ^J:   Ans Zeilenanfang/Zeilenende        */
/* 0B */ xx,            /*         ^K:   Subprozessor ^K                    */
/* 0C */ p_fr_next,     /*         ^L:   weiter suchen / ersetzen           */
/* 0D */ ned_eval_feature,      /* ^M:   Leerzeile und naechste Zeile       */
/* 0E */ xx,            /*         ^N:   Leerzeile                          */
/* 0F */ xx,            /*         ^O:   Subprozessor ^O                    */

/* 10 */ xx,            /*         ^P:   Eingabe von speziellen Tasten      */
/* 11 */ xx,            /*         ^Q:   Subprozessor ^Q                    */
/* 12 */ ned_page_up,   /*         ^R:   Eine Seite hinauf                  */
/* 13 */ ned_cursor_left,       /*         ^S:   Cursor nach links                  */
/* 14 */ xx,            /*         ^T:   Turn Line: 2 Zeilen vertausch      */
/* 15 */ xx,            /*         ^U:                                      */
/* 16 */ xx,            /*         ^V:                                      */
/* 17 */ p_upscr,       /*         ^W:   Eine Zeile hinauf scrollen         */
/* 18 */ ned_cursor_down,/*        ^X:   Cursor eine Zeile hinunter         */
/* 19 */ xx,            /*         ^Y:                                      */
/* 1A */ p_dnscr,       /*         ^Z:   Eine Zeile hinunter scrollen       */
/* 1B */ vi_on,         /* ESC                                              */
/* 1C */ ned_cursor_right,      /* CURSOR        Cursor nach rechts                 */
/* 1D */ ned_cursor_left,       /* CURSOR        Cursor nach links                  */
/* 1E */ ned_cursor_up, /* CURSOR        Cursor eine Zeile hinauf           */
/* 1F */ ned_cursor_down,/* CURSOR       Cursor eine Zeile hinunter         */

/* 20 */ ned_cursor_right, xx, xx, xx, xx, xx, xx, xx,
/* 28 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 30 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 38 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 40 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 48 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 50 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 58 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 60 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 68 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 70 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 78 */ xx, xx, xx, xx, xx, xx, xx, xx,

/* 80 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 88 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 90 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* 98 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* A0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* A8 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* B0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* B8 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* C0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* C8 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* D0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* D8 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* E0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* E8 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* F0 */ xx, xx, xx, xx, xx, xx, xx, xx,
/* F8 */ xx, xx, xx, xx, xx, xx, xx, xx

/*
 *  FILE %ned/00/ned0016w.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe a (kein Praefix)/Control in WordStar Mode
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include Files fuer
 *                             jede Praefix-Gruppe
 *                 1996-05-16: isolated from ned0001a.c
 *  latest update: 1999-05-01 10:39:56
 *  $ID: $
 *
 */

/* 0. normale Zeichen; keine Prefix-Codes - - - - - - - - - - - - - - - - - */
/* 00 */ xx,            /* Char  0x00:   Funktionstasten-PFX bei PC         */
/* 01 */ p_word_left,   /*         ^A:   Wort nach links                    */
/* 02 */ vi_ex,         /*         ^B:   EX Mode                            */
/* 03 */ ned_page_down, /*         ^C:   Seite hinunter                     */
/* 04 */ ned_cursor_right,  /*     ^D:   Cursor nach rechts                 */
/* 05 */ ned_cursor_up, /*         ^E:   Cursor hinauf                      */
/* 06 */ p_word_right_beg,  /*     ^F:   Wort nach rechts                   */
/* 07 */ ned_del_char_right,/*     ^G:   ein Zeichen rechts loeschen        */
/* 08 */ ned_del_char_left, /* DEL ^H:   ein Zeichen links  loeschen        */
/* 09 */ tabulate,          /* TAB ^I:   Tabulator                          */
#ifdef MSDOS
/* 0A */ p_ax_lng,      /*         ^J:   Ans Zeilenanfang/Zeilenende        */
#else
/* 0A */ p_nl,          /*         ^J:   Leerzeile und naechste Zeile       */
#endif
/* 0B */ p_ctrlk,       /*         ^K:   Subprozessor ^K: ned0001k.c        */
/* 0C */ p_fr_next,     /*         ^L:   weiter suchen / ersetzen           */
/* 0D */ p_nl,          /*         ^M:   Leerzeile und naechste Zeile       */
/* 0E */ p_nl2,         /*         ^N:   Leerzeile                          */
/* 0F */ p_ctrlo,       /*         ^O:   Subprozessor ^O: ned0001o.c        */

/* 10 */ ned_ctrlp,     /*         ^P:   Eingabe von speziellen Tasten      */
/* 11 */ p_ctrlq,       /*         ^Q:   Subprozessor ^Q: ned0001q.c        */
/* 12 */ ned_page_up,   /*         ^R:   Eine Seite hinauf                  */
/* 13 */ ned_cursor_left,   /*     ^S:   Cursor nach links                  */
/* 14 */ p_turn_line,   /*         ^T:   Turn Line: 2 Zeilen vertausch      */
/* 15 */ p_ctrlu,       /*         ^U:   Subprocessor ^U: ned0001u.c        */
/* 16 */ p_ovins,       /*         ^V:   Toggle Insert/Overwrite            */
/* 17 */ p_upscr,       /*         ^W:   Eine Zeile hinauf scrollen         */
/* 18 */ ned_cursor_down,   /*     ^X:   Cursor eine Zeile hinunter         */
/* 19 */ ned_delete_line,   /*     ^Y:   Eine Zeile loeschen                */
/* 1A */ p_dnscr,           /*     ^Z:   Eine Zeile hinunter scrollen       */
/* 1B */ vi_on,             /* ESC       see: ned0001v.c                    */
/* 1C */ ned_cursor_right,      /* CURSOR Cursor nach rechts                */
/* 1D */ ned_cursor_left,       /* CURSOR Cursor nach links                 */
/* 1E */ ned_cursor_up,         /* CURSOR Cursor eine Zeile hinauf          */
/* 1F */ ned_cursor_down        /* CURSOR Cursor eine Zeile hinunter        */

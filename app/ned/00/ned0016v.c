/*
 *  FILE %ned/00/ned0016v.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe a (kein Praefix)/Control in real VI Mode
 *
 *  written:       1996-12-03
 *  latest update: 1997-08-03  9:50:35
 *  $Id: ned0016v.c,v 1.2 2002/10/18 05:56:19 gonter Exp $
 *
 */

/* 0. normale Zeichen; keine Prefix-Codes - - - - - - - - - - - - - - - - - */
/* 00 */ xx,            /* Char  0x00:   Funktionstasten-PFX bei PC         */
/* 01 */ p_ctrlu,               /* ^A: command_table_U     UNUSED IN VI     */
/* 02 */ ned_page_up,           /* ^B: page up             UNUSED IN VI     */
/* 03 */ xx,                    /* ^C:                     UNUSED IN VI     */
/* 04 */ ned_half_page_down,    /* ^D: (half) page down    UNUSED IN VI     */
/* 05 */ p_upscr,               /* ^E:                                      */
/* 06 */ ned_page_down,         /* ^F: page down           UNUSED IN VI     */
/* 07 */ xx,                    /* ^G:                                      */
/* 08 */ ned_del_char_left, /* DEL ^H:   ein Zeichen links  loeschen        */
/* 09 */ tabulate,      /* TAB     ^I:   Tabulator                          */
/* 0A */ p_nl,          /*         ^J:   Leerzeile und naechste Zeile       */
/* 0B */ p_ctrlk,               /* ^K: command_table_K;    UNUSED IN VI !!! */
/* 0C */ p_refresh,             /* ^L: redraw current window                */
/* 0D */ p_nl,          /*         ^M:   Leerzeile und naechste Zeile       */
/* 0E */ p_nl2,         /*         ^N:   Leerzeile                          */
/* 0F */ p_ctrlo,       /*         ^O:   Subprozessor ^O: ned0001o.c        */

/* 10 */ ned_cursor_up,         /* ^P:                                      */
/* 11 */ p_ctrlq,               /* ^Q: commant_table_Q:    UNUSED IN VI !!! */
/* 12 */ p_refresh,             /* ^R:                                      */
/* 13 */ xx,                    /* ^S                      UNUSED IN VI     */
/* 14 */ xx,                    /* ^T:                     UNUSED IN VI     */
/* 15 */ ned_half_page_up,      /* ^U: (half) page up      UNUSED IN VI     */
/* 16 */ ned_ctrlp,             /* ^V: quote next char     UNUSED IN VI     */
/* 17 */ vi_dkey,               /* ^W: VIM extensions      UNUSED IN VI !!! */
/* 18 */ p_ctrlu,               /* ^X:                     UNUSED IN VI     */
/* 19 */ p_dnscr,               /* ^Y:                                      */
/* 1A */ xx,                    /* ^Z:   Eingabe von speziellen Tasten      */
/* 1B */ vi_on,         /* ESC           see: ned0001v.c                    */
/* 1C */ xx,            /* CURSOR        Cursor nach rechts                 */
/* 1D */ q_eval_tag,    /* CURSOR        Cursor nach links                  */
/* 1E */ xx,            /* CURSOR        Cursor eine Zeile hinauf           */
/* 1F */ xx,            /* CURSOR        Cursor eine Zeile hinunter         */

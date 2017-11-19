/*
 *  FILE %ned/00/ned0001o.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe o: ^O
 *  included by ned0001.c
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include Files fuer
 *                             jede Praefix-Gruppe
 *  latest update: 1997-06-13 14:08:28
 *  $Id: ned0001o.c,v 1.2 2005/04/01 16:46:20 gonter Exp $
 *
 */

/* 3. Praefix Ctrl O: On Screen Operations  - - - - - - - - - - - - - - - - */
/* 00 */ xx,                    /* ^O                                       */
/* 01 */ p_ww,                  /* ^O^A: Word Wrap togglen                  */
/* 02 */ p_backcolnxt,          /* ^O^B: Hintergrundfarbe aendern           */
/* 03 */ p_colornxt,            /* ^O^C: Vordergrundfarbe aendern           */
/* 04 */ xx,                    /* ^O^D:                                    */
/* 05 */ xx,                    /* ^O^E:                                    */
/* 06 */ p_link_feature,        /* ^O^F: Open Feature Winow                 */
/* 07 */ p_refresh,             /* ^O^G: Aktuelles Window Refreshen         */
/* 08 */ ned_set_lookup_tag,    /* ^O^H: set tag after name lookup          */
/* 09 */ p_aitoggle,            /* ^O^I: Toggle Auto Indent Mode            */
/* 0A */ xx,                    /* ^O^J                                     */
/* 0B */ xx,                    /* ^O^K                                     */
/* 0C */ p_clone_window,        /* ^O^L                                     */
/* 0D */ ned_set_mark,          /* ^O^M: set mark tag                       */
/* 0E */ ned_pr_jump_to_line,   /* ^O^N: Sprung auf Zeile #                 */
/* 0F */ p_wdwopen,             /* ^O^O: Open New Window (unnamed)          */

/* 10 */ xx,                    /* ^O^P                                     */
/* 11 */ p_wdwqfile,            /* ^O^Q: Abandon File / Close Window        */
/* 12 */ p_ofile2,              /* ^O^R: Open Window / Read File            */
/* 13 */ p_rdsetup,             /* ^O^S: Read Setup File                    */
/* 14 */ p_refresh_all,         /* ^O^T: Alle Windows Refreshen             */
/* 15 */ p_format_SGML,         /* ^O^U: File Format SGML                   */
/* 16 */ p_format_ASCII,        /* ^O^V: File Format ASCII                  */
/* 17 */ p_wdwsize,             /* ^O^W: Window Groesse aendern             */
/* 18 */ xx,                    /* ^O^X                                     */
/* 19 */ ned_close_window,      /* ^O^Y: Close Window (if possible)         */
/* 1A */ p_clone_window,        /* ^O^Z: Open Window and Link               */
/* 1B */ xx,                    /* ^O^                                      */
/* 1C */ xx,                    /* ^O^                                      */
/* 1D */ xx,                    /* ^O^                                      */
/* 1E */ xx,                    /* ^O^                                      */
/* 1F */ xx,                    /* ^O^                                      */

/* 20 */ xx,                    /* ^O                                       */
/* 21 */ xx,                    /* ^O                                       */
/* 22 */ xx,                    /* ^O                                       */
/* 23 */ xx,                    /* ^O                                       */
/* 24 */ xx,                    /* ^O                                       */
/* 25 */ xx,                    /* ^O                                       */
/* 26 */ xx,                    /* ^O                                       */
/* 27 */ xx,                    /* ^O                                       */
/* 28 */ xx,                    /* ^O                                       */
/* 29 */ xx,                    /* ^O                                       */
/* 2A */ xx,                    /* ^O                                       */
/* 2B */ p_insblk,              /* ^O+: Eingabe Sperren / Toggle            */
/* 2C */ TK(ned_tk_aw_iconify), /* ^O,                                      */
/* 2D */ QQdeb,                 /* ^O-: Debugger Zeile umschalten           */
/* 2E */ TK(ned_tk_aw_withdraw),/* ^O.                                      */
/* 2F */ TK(ned_tk_aw_deiconify),/* ^O/ (does this work??)                  */

/* 30 */ xx,                    /* ^O0                                      */
/* 31 */ p_jmpwdw,              /* ^O1: Sprung ins Window # 1               */
/* 32 */ p_jmpwdw,              /* ^O                                       */
/* 33 */ p_jmpwdw,              /* ^O                                       */
/* 34 */ p_jmpwdw,              /* ^O                                       */
/* 35 */ p_jmpwdw,              /* ^O                                       */
/* 36 */ p_jmpwdw,              /* ^O                                       */
/* 37 */ p_jmpwdw,              /* ^O                                       */
/* 38 */ p_jmpwdw,              /* ^O                                       */
/* 39 */ p_jmpwdw,              /* ^O                                       */
/* 3A */ xx,                    /* ^O:                                      */
/* 3B */ xx,                    /* ^O;                                      */
/* 3C */ ned_markup_block_prompt, /* ^O<                                    */
/* 3D */ xx,                    /* ^O=                                      */
/* 3E */ xx,                    /* ^O>                                      */
/* 3F */ TK(ned_tk_aw_save_withdraw),/* ^O?                                 */

/* 40 */ xx,                    /* ^O@                                      */
/* 41 */ p_ww,                  /* ^OA Word Wrap togglen                    */
/* 42 */ p_backcolnxt,          /* ^OB                                      */
/* 43 */ p_colornxt,            /* ^OC                                      */
/* 44 */ xx,                    /* ^OD                                      */
/* 45 */ xx,                    /* ^OE                                      */
/* 46 */ p_link_feature,        /* ^OF Open Feature Winow                   */
/* 47 */ p_refresh,             /* ^OG                                      */
/* 48 */ ned_set_lookup_tag,    /* ^OH: set tag after name lookup           */
/* 49 */ p_aitoggle,            /* ^OI                                      */
/* 4A */ xx,                    /* ^OJ                                      */
/* 4B */ xx,                    /* ^OK                                      */
/* 4C */ p_clone_window,        /* ^OL                                      */
/* 4D */ ned_set_mark,          /* ^OM: set mark tag                        */
/* 4E */ ned_pr_jump_to_line,   /* ^ON                                      */
/* 4F */ p_wdwopen,             /* ^OO                                      */

/* 50 */ xx,                    /* ^OP                                      */
/* 51 */ p_wdwqfile,            /* ^OQ                                      */
/* 52 */ p_ofile1,              /* ^OR                                      */
/* 53 */ p_rdsetup,             /* ^OS                                      */
/* 54 */ p_refresh_all,         /* ^OT                                      */
/* 55 */ p_format_SGML,         /* ^OU: File Format SGML                    */
/* 56 */ p_format_ASCII,        /* ^OV: File Format ASCII                   */
/* 57 */ p_wdwsize,             /* ^OW                                      */
/* 58 */ xx,                    /* ^OX                                      */
/* 59 */ ned_close_window,      /* ^OY                                      */
/* 5A */ p_clone_window,        /* ^OZ Open Window and Link                 */
/* 5B */ xx,                    /* ^O[                                      */
/* 5C */ xx,                    /* ^O\                                      */
/* 5D */ xx,                    /* ^O]                                      */
/* 5E */ pico_mode,             /* ^O^                                      */
/* 5F */ xx,                    /* ^O_                                      */

/* 60 */ vi_mode,               /* ^O`                                      */
/* 61 */ p_ww,                  /* ^Oa: Word Wrap togglen                   */
/* 62 */ p_backcolnxt,          /* ^Ob                                      */
/* 63 */ p_colornxt,            /* ^Oc                                      */
/* 64 */ xx,                    /* ^Od                                      */
/* 65 */ xx,                    /* ^Oe                                      */
/* 66 */ p_link_feature,        /* ^Of: Open Feature Window                 */
/* 67 */ p_refresh,             /* ^Og                                      */
/* 68 */ ned_set_lookup_tag,    /* ^Oh: set tag after name lookup           */
/* 69 */ p_aitoggle,            /* ^Oi                                      */
/* 6A */ xx,                    /* ^Oj                                      */
/* 6B */ xx,                    /* ^Ok                                      */
/* 6C */ p_clone_window,        /* ^Ol                                      */
/* 6D */ ned_set_mark,          /* ^Om: set mark tag                        */
/* 6E */ ned_pr_jump_to_line,   /* ^On                                      */
/* 6F */ p_wdwopen,             /* ^Oo                                      */

/* 70 */ xx,                    /* ^Op                                      */
/* 71 */ p_wdwqfile,            /* ^Oq                                      */
/* 72 */ p_ofile1,              /* ^Or                                      */
/* 73 */ p_rdsetup,             /* ^Os                                      */
/* 74 */ p_refresh_all,         /* ^Ot                                      */
/* 75 */ p_format_SGML,         /* ^Ou: File Format SGML                    */
/* 76 */ p_format_ASCII,        /* ^Ov: File Format ASCII                   */
/* 77 */ p_wdwsize,             /* ^Ow                                      */
/* 78 */ xx,                    /* ^Ox                                      */
/* 79 */ ned_close_window,      /* ^Oy                                      */
/* 7A */ p_clone_window,        /* ^Oz: Open Window and Link                */
/* 7B */ xx,                    /* ^O{                                      */
/* 7C */ xx,                    /* ^O|                                      */
/* 7D */ xx,                    /* ^O}                                      */
/* 7E */ wordstar_mode,         /* ^O~                                      */
/* 7F */ xx                     /* ^O                                       */

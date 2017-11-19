/*
 *  FILE %ned/00/ned0001f.c
 *
 *  jump table for editor NED: 
 *  group f: IBM-PC function keys
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include Files fuer jede
 *                             Praefix-Gruppe
 *  latest update: 2001-02-12  0:37:48
 *  $Id: ned0001f.c,v 1.3 2001/02/12 00:03:14 gonter Exp $
 *
 */

/* 4. Praefix: Funktionstasten der IBM Tastatur - - - - - - - - - - - - - - */
/* 00 */ xx,                    /*                                          */
/* 01 */ xx,                    /* ALT-ESC                                  */
/* 02 */ xx,                    /*                                          */
/* 03 */ xx,                    /*                                          */
/* 04 */ xx,                    /*                                          */
/* 05 */ xx,                    /*                                          */
/* 06 */ xx,                    /*                                          */
/* 07 */ xx,                    /*                                          */
/* 08 */ xx,                    /*                                          */
/* 09 */ xx,                    /*                                          */
/* 0A */ xx,                    /*                                          */
/* 0B */ xx,                    /*                                          */
/* 0C */ xx,                    /*                                          */
/* 0D */ xx,                    /*                                          */
/* 0E */ xx,                    /*                                          */
/* 0F */ ned_set_mark,          /* Shift-TAB: set mark tag                  */

/* 10 */ ned_jmp_marker_1,      /* ALT-Q:                                   */
/* 11 */ p_link_feature,        /* ALT-W: Feature Window oeffnen            */
/* 12 */ p_edsetup,             /* ALT-E: Setup File editieren              */
/* 13 */ p_rdsetup,             /* ALT-R: Setup File einlesen               */
/* 14 */ p_window_menu,         /* ALT-T: Window Menu                       */
/* 15 */ ned_delete_word,       /* ALT-Y: Delete Word Right                 */
/* 16 */ ned_line_end_UNIX,     /* ALT-U: -> UNIX Line End                  */
/* 17 */ ned_line_end_MSDOS,    /* ALT-I: -> MSDOS Line End                 */
/* 18 */ ned_memorize_location, /* ALT-O: store frame or file               */
/* 19 */ p_feature_prev,        /* ALT-P: Jump 2 Prev Feature               */
/* 1A */ p_find_higher_bracket, /* ALT-[                                    */
/* 1B */ p_find_lower_bracket,  /* ALT-]                                    */
/* 1C */ xx,                    /*                                          */
/* 1D */ xx,                    /*                                          */
/* 1E */ ned_show_author,       /* ALT-A: Author ausgeben                   */
/* 1F */ xx,                    /* ALT-S:                                   */

/* 20 */ p_mac_define,          /* ALT-D: Define Makro                      */
/* 21 */ p_feature_set,         /* ALT-F: Feature setzen                    */
/* 22 */ p_feature_reset,       /* ALT-G: Feature loeschen                  */
/* 23 */ ned_set_hyx_l,         /* ALT-H: hyx.l setzen                      */
/* 24 */ ned_set_SGML_tag,      /* ALT-J: SGML Tag setzen                   */
/* 25 */ ned_set_SGML_entity,   /* ALT-K: SGML Entity setzen                */
/* 26 */ DOSPRIM(p_switch_line_mode), /* ALT-L: lines ...                   */
/* 27 */ xx,                    /* ALT-;                                    */
/* 28 */ xx,                    /* ALT-'                                    */
/* 29 */ ned_read_entity,       /* ALT-(backtick)                           */
/* 2A */ xx,                    /*                                          */
/* 2B */ p_find_matching_bracket,/*ALT-\                                    */
/* 2C */ xx,                    /* ALT-Z:                                   */
/* 2D */ ned_eval_feature,      /* ALT-X: Ausfuehrung eines Features        */
/* 2E */ p_cross_ref,           /* ALT-C: Cross Referencing                 */
/* 2F */ ned_eval_block,        /* ALT-V: Ausfuehrung eines Blocks          */

/* 30 */ xx,                    /* ALT-B:                                   */
/* 31 */ p_feature_next,        /* ALT-N: Jump 2 Next Feature               */
/* 32 */ p_menue,               /* ALT-M: Menue aktivieren                  */
/* 33 */ xx,                    /* ALT-,                                    */
/* 34 */ xx,                    /* ALT-.                                    */
/* 35 */ xx,                    /* ALT-/                                    */
/* 36 */ xx,                    /*                                          */
/* 37 */ xx,                    /* ALT-NKP-*                                */
/* 38 */ xx,                    /*                                          */
/* 39 */ xx,                    /*                                          */
/* 3A */ xx,                    /*                                          */
/* 3B */ p_macro01,             /* F1: Makro 01                             */
/* 3C */ p_macro02,             /* F2                                       */
/* 3D */ p_macro03,             /* F3                                       */
/* 3E */ p_macro04,             /* F4                                       */
/* 3F */ p_refresh,             /* F5                                       */

/* 40 */ p_macro06,             /* F6                                       */
/* 41 */ p_sx,                  /* F7: save and exit                        */
/* 42 */ p_ssave,               /* F8: Save actual Window if Update, Close  */
/* 43 */ p_activate_fr_root,    /* F9: root frame in local cluster          */
/* 44 */ p_activate_cl1,        /* F10: special cluster 1 (help)            */
/* 45 */ xx,                    /*                                          */
/* 46 */ xx,                    /*                                          */
/* 47 */ ned_jmp_boln,          /* HOME: Anfang der Zeile                   */
/* 48 */ ned_cursor_up,         /* CURSOR UP                                */
/* 49 */ ned_page_up,           /* PAGE UP                                  */
/* 4A */ xx,                    /* ALT-NKP--                                */
/* 4B */ ned_cursor_left,       /* CURSOR LEFT                              */
/* 4C */ xx,                    /*                                          */
/* 4D */ ned_cursor_right,      /* CURSOR RIGHT                             */
/* 4E */ xx,                    /* ALT-NKP-+                                */
/* 4F */ ned_jmp_eoln,          /* END: Ende der Zeile                      */

/* 50 */ ned_cursor_down,       /* CURSOR DOWN                              */
/* 51 */ ned_page_down,         /* PAGE DOWN                                */
/* 52 */ p_ovins,               /* INSERT                                   */
/* 53 */ ned_del_char_right,    /* DELETE                                   */
/* 54 */ p_macro11,             /* SF1                                      */
/* 55 */ p_macro12,             /* SF2                                      */
/* 56 */ p_macro13,             /* SF3                                      */
/* 57 */ p_macro14,             /* SF4                                      */
/* 58 */ p_refresh_all,         /* SF5                                      */
/* 59 */ p_macro16,             /* SF6                                      */
/* 5A */ p_macro17,             /* SF7                                      */
/* 5B */ ned_ssave_all,         /* SF8                                      */
/* 5C */ p_activate_fr_notes,   /* SF9: notes frame in local cluster        */
/* 5D */ p_activate_cl2,        /* SF10: special cluster 2 (notes)          */
/* 5E */ p_macro21,             /* CF1                                      */
/* 5F */ p_macro22,             /* CF2                                      */

/* 60 */ p_macro23,             /* CF3                                      */
/* 61 */ p_macro24,             /* CF4                                      */
/* 62 */ p_colornxt,            /* CF5                                      */
/* 63 */ p_macro26,             /* CF6                                      */
/* 64 */ p_macro27,             /* CF7                                      */
/* 65 */ p_macro28,             /* CF8                                      */
/* 66 */ p_activate_fr_help,    /* CF9: help frame in local cluster         */
/* 67 */ p_activate_cl3,        /* CF10: special cluster 3                  */
/* 68 */ p_macro31,             /* AF1                                      */
/* 69 */ p_macro32,             /* AF2                                      */
/* 6A */ p_macro33,             /* AF3                                      */
/* 6B */ p_macro34,             /* AF4                                      */
/* 6C */ p_backcolnxt,          /* AF5                                      */
/* 6D */ p_macro36,             /* AF6                                      */
/* 6E */ p_macro37,             /* AF7                                      */
/* 6F */ p_macro38,             /* AF8                                      */

/* 70 */ ned_p_activate_cl_fr,  /* AF9: prompt for cluster and frame        */
/* 71 */ p_activate_cl4,        /* AF10: special cluster 4                  */
/* 72 */ xx,                    /* Ctrl-PrtScr                              */
/* 73 */ p_word_left,           /* Ctrl-Left                                */
/* 74 */ p_word_right_beg,      /* Ctrl-Right                               */
/* 75 */ xx,                    /* Ctrl-End                                 */
/* 76 */ pq_dn,                 /* Ctrl-PgDn                                */
/* 77 */ xx,                    /* Ctrl-Home                                */
/* 78 */ p_macro41,             /* ALT-1:                                   */
/* 79 */ p_macro42,             /* ALT-2:                                   */
/* 7A */ p_macro43,             /* ALT-3:                                   */
/* 7B */ p_macro44,             /* ALT-4:                                   */
/* 7C */ p_macro45,             /* ALT-5:                                   */
/* 7D */ p_macro46,             /* ALT-6:                                   */
/* 7E */ p_macro47,             /* ALT-7:                                   */
/* 7F */ p_macro48,             /* ALT-8:                                   */

/* 80 */ p_macro49,             /* ALT-9:                                   */
/* 81 */ p_macro40,             /* ALT-0:                                   */
/* 82 */ p_alt_minus,           /* ALT--: Character 196, 0xC4               */
/* 83 */ p_alt_gleich,          /* ALT-=: Character 205, 0xCD               */
/* 84 */ pq_up,                 /* Ctrl-PgUp                                */
/* 85 */ p_split_join,          /* F11                                      */
/* 86 */ xx,                    /* F12                                      */
/* 87 */ xx,                    /* SF11                                     */
/* 88 */ xx,                    /* SF12                                     */
/* 89 */ xx,                    /* CF11                                     */
/* 8A */ xx,                    /* CF12                                     */
/* 8B */ xx,                    /* AF11                                     */
/* 8C */ xx,                    /* AF12                                     */
/* 8D */ ned_page_up,           /* CTRL-CURSOR-UP                           */
/* 8E */ xx,                    /*                                          */
/* 8F */ xx,                    /*                                          */

/* 90 */ xx,                    /*                                          */
/* 91 */ ned_page_down,         /* CTRL-CURSOR-DOWN                         */
/* 92 */ xx,                    /* CTRL-Insert                              */
/* 93 */ xx,                    /* CTRL-Delete                              */
/* 94 */ ned_set_lookup_tag_fr, /* CTRL-TAB                                 */
/* 95 */ xx,                    /*                                          */
/* 96 */ xx,                    /*                                          */
/* 97 */ p_logic_link_up,       /* ALT-HOME                                 */
/* 98 */ ned_page_up,           /* ALT-CURSOR-UP                            */
/* 99 */ p_logic_link_prev,     /* ALT-PGUP                                 */
/* 9A */ xx,                    /*                                          */
/* 9B */ ned_jmp_boln,          /* ALT-CURSOR-LEFT                          */
/* 9C */ xx,                    /*                                          */
/* 9D */ ned_jmp_eoln,          /* ALT-CURSOR-RIGHT                         */
/* 9E */ xx,                    /*                                          */
/* 9F */ p_logic_link_menu,     /* ALT-END                                  */

/* A0 */ ned_page_down,         /* ALT-CURSOR-DOWN                          */
/* A1 */ p_logic_link_next,     /* ALT-PGDN                                 */
/* A2 */ xx,                    /* ALT-INS                                  */
/* A3 */ xx,                    /* ALT-DEL                                  */
/* A4 */ xx,                    /* ALT-NKP-/                                */
/* A5 */ ned_set_lookup_tag,    /* ALT-TAB: set tag after name lookup       */
/* A6 */ xx,                    /* ALT-NKP-ENTER                            */
/* A7 */ xx,                    /*                                          */
/* A8 */ xx,                    /*                                          */
/* A9 */ xx,                    /*                                          */
/* AA */ xx,                    /*                                          */
/* AB */ xx,                    /*                                          */
/* AC */ xx,                    /*                                          */
/* AD */ xx,                    /*                                          */
/* AE */ xx,                    /*                                          */
/* AF */ xx,                    /*                                          */

/* B0 */ xx,                    /*                                          */
/* B1 */ xx,                    /*                                          */
/* B2 */ xx,                    /*                                          */
/* B3 */ xx,                    /*                                          */
/* B4 */ xx,                    /*                                          */
/* B5 */ xx,                    /*                                          */
/* B6 */ xx,                    /*                                          */
/* B7 */ xx,                    /*                                          */
/* B8 */ xx,                    /*                                          */
/* B9 */ xx,                    /*                                          */
/* BA */ xx,                    /*                                          */
/* BB */ xx,                    /*                                          */
/* BC */ xx,                    /*                                          */
/* BD */ xx,                    /*                                          */
/* BE */ xx,                    /*                                          */
/* BF */ xx,                    /*                                          */

/* C0 */ xx,                    /*                                          */
/* C1 */ xx,                    /*                                          */
/* C2 */ xx,                    /*                                          */
/* C3 */ xx,                    /*                                          */
/* C4 */ xx,                    /*                                          */
/* C5 */ xx,                    /*                                          */
/* C6 */ xx,                    /*                                          */
/* C7 */ xx,                    /*                                          */
/* C8 */ xx,                    /*                                          */
/* C9 */ xx,                    /*                                          */
/* CA */ xx,                    /*                                          */
/* CB */ xx,                    /*                                          */
/* CC */ xx,                    /*                                          */
/* CD */ xx,                    /*                                          */
/* CE */ xx,                    /*                                          */
/* CF */ xx,                    /*                                          */

/* D0 */ xx,                    /*                                          */
/* D1 */ xx,                    /*                                          */
/* D2 */ xx,                    /*                                          */
/* D3 */ xx,                    /*                                          */
/* D4 */ xx,                    /*                                          */
/* D5 */ xx,                    /*                                          */
/* D6 */ xx,                    /*                                          */
/* D7 */ xx,                    /*                                          */
/* D8 */ xx,                    /*                                          */
/* D9 */ xx,                    /*                                          */
/* DA */ xx,                    /*                                          */
/* DB */ xx,                    /*                                          */
/* DC */ xx,                    /*                                          */
/* DD */ xx,                    /*                                          */
/* DE */ xx,                    /*                                          */
/* DF */ xx,                    /*                                          */

/* E0 */ xx,                    /*                                          */
/* E1 */ xx,                    /*                                          */
/* E2 */ xx,                    /*                                          */
/* E3 */ xx,                    /*                                          */
/* E4 */ xx,                    /*                                          */
/* E5 */ xx,                    /*                                          */
/* E6 */ xx,                    /*                                          */
/* E7 */ xx,                    /*                                          */
/* E8 */ xx,                    /*                                          */
/* E9 */ xx,                    /*                                          */
/* EA */ xx,                    /*                                          */
/* EB */ xx,                    /*                                          */
/* EC */ xx,                    /*                                          */
/* ED */ xx,                    /*                                          */
/* EE */ xx,                    /*                                          */
/* EF */ xx,                    /*                                          */

/* F0 */ xx,                    /*                                          */
/* F1 */ xx,                    /*                                          */
/* F2 */ xx,                    /*                                          */
/* F3 */ xx,                    /*                                          */
/* F4 */ xx,                    /*                                          */
/* F5 */ xx,                    /*                                          */
/* F6 */ xx,                    /*                                          */
/* F7 */ xx,                    /*                                          */
/* F8 */ xx,                    /*                                          */
/* F9 */ xx,                    /*                                          */
/* FA */ xx,                    /*                                          */
/* FB */ xx,                    /*                                          */
/* FC */ xx,                    /*                                          */
/* FD */ xx,                    /*                                          */
/* FE */ xx,                    /*                                          */
/* FF */ xx                     /*                                          */

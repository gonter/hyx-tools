/*
 *  FILE %ned/00/ned0001t.c
 *
 *  jump table for editor NED: 
 *  group t: X-Windows (Tk) model
 *
 *  written:       1995-10-06
 *  latest update: 2001-02-11 12:41:24
 *  $Id: ned0001t.c,v 1.5 2001/04/01 22:45:01 gonter Exp $
 *
 */

/* 0x00 */ xx,                          /* dummy key code                   */
/* 0x01 */ ned_set_mark,                /* SHIFT-TAB                        */
/* 0x02 */ ned_set_lookup_tag_fr,       /* CTRL-TAB                         */
/* 0x03 */ ned_set_lookup_tag,          /* ALT-TAB                          */
/* 0x04 */ xx,
/* 0x05 */ xx,
/* 0x06 */ xx,
/* 0x07 */ xx,
/* 0x08 */ ned_del_char_left,           /* XK_BackSpace  back space         */
/* 0x09 */ tabulate,                    /* XK_Tab                           */
/* 0x0A */ p_nl,                        /* XK_Linefeed  Linefeed, LF        */
/* 0x0B */ xx,                          /* XK_Clear                         */
/* 0x0C */ xx,
/* 0x0D */ p_nl,                        /* XK_Return  Return, enter         */
/* 0x0E */ xx,
/* 0x0F */ xx,
/* 0x10 */ xx,
/* 0x11 */ xx,
/* 0x12 */ ned_read_entity,             /* ALT-`                            */
/* 0x13 */ xx,                          /* XK_Pause  Pause, hold            */
/* 0x14 */ xx,                          /* XK_Scroll_Lock                   */
/* 0x15 */ xx,                          /* ALT-{                            */
/* 0x16 */ xx,                          /* ALT-|                            */
/* 0x17 */ xx,                          /* ALT-}                            */
/* 0x18 */ xx,                          /* ALT-~                            */
/* 0x19 */ xx,
/* 0x1A */ xx,
/* 0x1B */ vi_on,                       /* XK_Escape                        */
/* 0x1C */ xx,
/* 0x1D */ xx,
/* 0x1E */ xx,
/* 0x1F */ xx,

/* 0x20 .. 0x4F: ALT-0 .. ALT-_ shifted down                                */
/* 0x20 */ p_macro40,                   /* ALT-0                            */
/* 0x21 */ p_macro41,                   /* ALT-1                            */
/* 0x22 */ p_macro42,
/* 0x23 */ p_macro43,
/* 0x24 */ p_macro44,
/* 0x25 */ p_macro45,
/* 0x26 */ p_macro46,
/* 0x27 */ p_macro47,
/* 0x28 */ p_macro48,
/* 0x29 */ p_macro49,                   /* ALT-9                            */
/* 0x2A */ xx,                          /* XK_Zenkaku_Hankaku  Zenkaku/Hankaku toggle */
/* 0x2B */ xx,                          /* XK_Touroku  Add to Dictionary    */
/* 0x2C */ xx,                          /* XK_Massyo  Delete from Dictionary */
/* 0x2D */ xx,                          /* XK_Kana_Lock  Kana Lock          */
/* 0x2E */ xx,                          /* XK_Kana_Shift  Kana Shift        */
/* 0x2F */ xx,                          /* XK_Eisu_Shift  Alphanumeric Shift */
/* 0x30 */ xx,                          /* XK_Eisu_toggle  Alphanumeric toggle */
/* 0x31 */ ned_show_author,             /* ALT-A                            */
/* 0x32 */ xx,                          /* ALT-B */
/* 0x33 */ p_cross_ref,                 /* ALT-C */
/* 0x34 */ p_mac_define,                /* ALT-D */
/* 0x35 */ p_edsetup,                   /* ALT-E */
/* 0x36 */ p_feature_set,               /* ALT-F */
/* 0x37 */ p_feature_reset,             /* ALT-G */
/* 0x38 */ ned_set_hyx_l,               /* ALT-H */
/* 0x39 */ ned_line_end_MSDOS,          /* ALT-I */
/* 0x3A */ ned_set_SGML_tag,            /* ALT-J */
/* 0x3B */ ned_set_SGML_entity,         /* ALT-K */
/* 0x3C */ xx,                          /* ALT-L: DOS(Lines)                */
/* 0x3D */ xx,                          /* ALT-M: DOS(Menu)                 */
/* 0x3E */ p_feature_next,              /* ALT-N */
/* 0x3F */ ned_memorize_location,       /* ALT-O */
/* 0x40 */ p_feature_prev,              /* ALT-P */
/* 0x41 */ ned_jmp_marker_1,            /* ALT-Q */
/* 0x42 */ p_rdsetup,                   /* ALT-R */
/* 0x43 */ xx,                          /* ALT-S */
/* 0x44 */ p_window_menu,               /* ALT-T */
/* 0x45 */ ned_line_end_UNIX,           /* ALT-U */
/* 0x46 */ ned_eval_block,              /* ALT-V */
/* 0x47 */ p_link_feature,              /* ALT-W */
/* 0x48 */ ned_eval_feature,            /* ALT-X */
/* 0x49 */ ned_delete_word,             /* ALT-Y */
/* 0x4A */ xx,                          /* ALT-Z */
/* 0x4B */ p_find_higher_bracket,       /* ALT-[                            */
/* 0x4C */ p_find_matching_bracket,     /* ALT-\                            */
/* 0x4D */ p_find_lower_bracket,        /* ALT-]                            */
/* 0x4E */ xx,                          /* ALT-^                            */
/* 0x4F */ xx,                          /* ALT-_                            */
/* 0x50 */ ned_jmp_boln,                /* XK_Home                          */
/* 0x51 */ ned_cursor_left,             /* XK_Left  Move left, left arrow   */
/* 0x52 */ ned_cursor_up,               /* XK_Up    Move up, up arrow       */
/* 0x53 */ ned_cursor_right,            /* XK_Right Move right, right arrow */
/* 0x54 */ ned_cursor_down,             /* XK_Down  Move down, down arrow   */
/* 0x55 */ ned_page_up,                 /* XK_Prior Prior, previous         */
/* 0x56 */ ned_page_down,               /* XK_Next  Next                    */
/* 0x57 */ ned_jmp_eoln,                /* XK_End   EOL                     */
/* 0x58 */ ned_jmp_boln,                /* XK_Begin BOL                     */
/* 0x59 */ xx,                          /* ALT-:                            */
/* 0x5A */ xx,                          /* ALT-;                            */
/* 0x5B */ xx,                          /* ALT-<                            */
/* 0x5C */ xx,                          /* ALT-=                            */
/* 0x5D */ xx,                          /* ALT->                            */
/* 0x5E */ xx,                          /* ALT-?                            */
/* 0x5F */ xx,                          /* ALT-@                            */
/* 0x60 */ xx,                          /* XK_Select  Select, mark          */
/* 0x61 */ xx,                          /* XK_Print                         */
/* 0x62 */ ned_eval_feature,            /* XK_Execute  Execute, run, do     */
/* 0x63 */ p_ovins,                     /* XK_Insert  Insert, insert here   */
/* 0x64 */ xx,
/* 0x65 */ xx,                          /* XK_Undo  Undo, oops              */
/* 0x66 */ xx,                          /* XK_Redo  redo, again             */
/* 0x67 */ xx,                          /* XK_Menu                          */
/* 0x68 */ p_find,                      /* XK_Find  Find, search            */
/* 0x69 */ xx,                          /* XK_Cancel  Cancel, stop, abort, exit */
/* 0x6A */ p_activate_cl1,              /* XK_Help  Help, ?                 */
/* 0x6B */ xx,                          /* XK_Break                         */
/* 0x6C */ xx,
/* 0x6D */ xx,
/* 0x6E */ xx,                          /* ALT-Blank                        */
/* 0x6F */ xx,                          /* ALT-!                            */
/* 0x70 */ xx,                          /* ALT-"                            */
/* 0x71 */ xx,                          /* ALT-#                            */
/* 0x72 */ xx,                          /* ALT-$                            */
/* 0x73 */ xx,                          /* ALT-%                            */
/* 0x74 */ xx,                          /* ALT-&                            */
/* 0x75 */ xx,                          /* ALT-'                            */
/* 0x76 */ xx,                          /* ALT-(                            */
/* 0x77 */ xx,                          /* ALT-)                            */
/* 0x78 */ xx,                          /* ALT-*                            */
/* 0x79 */ xx,                          /* ALT-+                            */
/* 0x7A */ xx,                          /* ALT-,                            */
/* 0x7B */ xx,                          /* ALT--                            */
/* 0x7C */ xx,                          /* ALT-.                            */
/* 0x7D */ xx,                          /* ALT-/                            */
/* 0x7E */ xx,                          /* XK_script_switch  Alias for mode_switch */
/* 0x7F */ xx,                          /* XK_Num_Lock                      */
/* 0x80 */ xx,                          /* XK_KP_Space  space               */
/* 0x81 */ xx,
/* 0x82 */ xx,
/* 0x83 */ xx,
/* 0x84 */ xx,
/* 0x85 */ xx,
/* 0x86 */ xx,
/* 0x87 */ xx,
/* 0x88 */ xx,
/* 0x89 */ tabulate,                    /* XK_KP_Tab                        */
/* 0x8A */ xx,
/* 0x8B */ xx,
/* 0x8C */ xx,
/* 0x8D */ p_nl,                        /* XK_KP_Enter  enter               */
/* 0x8E */ xx,
/* 0x8F */ xx,
/* 0x90 */ xx,
/* 0x91 */ xx,                          /* XK_KP_F1  PF1, KP_A, ...         */
/* 0x92 */ xx,                          /* XK_KP_F2                         */
/* 0x93 */ xx,                          /* XK_KP_F3                         */
/* 0x94 */ xx,                          /* XK_KP_F4                         */
/* 0x95 */ xx,
/* 0x96 */ xx,
/* 0x97 */ xx,

/* 0x98 -  0xA9: cursor pad with CTRL and ALT, shifted up                   */
/* 0x98 */ xx,                          /* CTRL-Home                        */
/* 0x99 */ p_word_left,                 /* CTRL-Left                        */
/* 0x9A */ ned_ftr_shift_up,            /* CTRL-Up                          */
/* 0x9B */ p_word_right_beg,            /* CTRL-Right                       */
/* 0x9C */ ned_ftr_shift_down,          /* CTRL-Down                        */
/* 0x9D */ pq_up,                       /* CTRL-PGUP                        */
/* 0x9E */ pq_dn,                       /* CTRL-PGDN                        */
/* 0x9F */ xx,                          /* CTRL-End                         */
/* 0xA0 */ xx,                          /* CTRL-Home (Begin)                */

/* 0xA1 */ p_logic_link_up,             /* ALT-Home                         */
/* 0xA2 */ ned_jmp_boln,                /* ALT-Left                         */
/* 0xA3 */ ned_page_up,                 /* ALT-Up                           */
/* 0xA4 */ ned_jmp_eoln,                /* ALT-Right                        */
/* 0xA5 */ ned_page_down,               /* ALT-Down                         */
/* 0xA6 */ p_logic_link_prev,           /* ALT-PGUP                         */
/* 0xA7 */ p_logic_link_next,           /* ALT-PGDN                         */
/* 0xA8 */ p_logic_link_menu,           /* ALT-End                          */
/* 0xA9 */ p_logic_link_up,             /* ALT-Home (Begin)                 */

/* 0xAA..0xB9: numeric keypad symbols together with ALT                     */
/* 0xAA */ xx,                          /* XK_KP_Multiply                   */
/* 0xAB */ xx,                          /* XK_KP_Add                        */
/* 0xAC */ xx,                          /* XK_KP_Separator  separator, often comma */
/* 0xAD */ xx,                          /* XK_KP_Subtract                   */
/* 0xAE */ xx,                          /* XK_KP_Decimal                    */
/* 0xAF */ xx,                          /* XK_KP_Divide                     */
/* 0xB0 */ xx,                          /* XK_KP_0                          */
/* 0xB1 */ xx,                          /* XK_KP_1                          */
/* 0xB2 */ xx,                          /* XK_KP_2                          */
/* 0xB3 */ xx,                          /* XK_KP_3                          */
/* 0xB4 */ xx,                          /* XK_KP_4                          */
/* 0xB5 */ xx,                          /* XK_KP_5                          */
/* 0xB6 */ xx,                          /* XK_KP_6                          */
/* 0xB7 */ xx,                          /* XK_KP_7                          */
/* 0xB8 */ xx,                          /* XK_KP_8                          */
/* 0xB9 */ xx,                          /* XK_KP_9                          */
/* 0xBA */ xx,
/* 0xBB */ xx,
/* 0xBC */ xx,
/* 0xBD */ xx,                          /* XK_KP_Equal  equals              */
/* 0xBE */ p_macro01,                   /* XK_F1                            */
/* 0xBF */ p_macro02,                   /* XK_F2                            */
/* 0xC0 */ p_macro03,                   /* XK_F3                            */
/* 0xC1 */ p_macro04,                   /* XK_F4                            */
/* 0xC2 */ p_refresh,                   /* XK_F5                            */
/* 0xC3 */ p_macro06,                   /* XK_F6                            */
/* 0xC4 */ p_sx,                        /* XK_F7                            */
/* 0xC5 */ p_ssave,                     /* XK_F8                            */
/* 0xC6 */ p_activate_fr_root,          /* XK_F9                            */
/* 0xC7 */ p_activate_cl1,              /* XK_F10                           */
/* 0xC8 */ p_split_join,                /* F11                              */
/* 0xC9 */ xx,                          /* F12                              */
/* 0xCA */ p_macro11,                   /* SF1                              */
/* 0xCB */ p_macro12,                   /* SF2                              */
/* 0xCC */ p_macro13,                   /* SF3                              */
/* 0xCD */ p_macro14,                   /* SF4                              */
/* 0xCE */ p_refresh_all,               /* SF5                              */
/* 0xCF */ p_macro16,                   /* SF6                              */
/* 0xD0 */ p_macro17,                   /* SF7                              */
/* 0xD1 */ ned_ssave_all,               /* SF8                              */
/* 0xD2 */ p_activate_fr_notes,         /* SF9                              */
/* 0xD3 */ p_activate_cl2,              /* SF10                             */
/* 0xD4 */ xx,                          /* SF11                             */
/* 0xD5 */ xx,                          /* SF12                             */
/* 0xD6 */ p_macro21,                   /* CF1                              */
/* 0xD7 */ p_macro22,                   /* CF2                              */
/* 0xD8 */ p_macro23,                   /* CF3                              */
/* 0xD9 */ p_macro24,                   /* CF4                              */
/* 0xDA */ p_colornxt,                  /* CF5                              */
/* 0xDB */ p_macro26,                   /* CF6                              */
/* 0xDC */ p_macro27,                   /* CF7                              */
/* 0xDD */ p_macro28,                   /* CF8                              */
/* 0xDE */ p_activate_fr_help,          /* CF9                              */
/* 0xDF */ p_activate_cl3,              /* CF10                             */
/* 0xE0 */ xx,                          /* CF11                             */
/* 0xE1 */ xx,                          /* XK_Shift_L     Left shift        */
/* 0xE2 */ xx,                          /* XK_Shift_R     Right shift       */
/* 0xE3 */ xx,                          /* XK_Control_L   Left control      */
/* 0xE4 */ xx,                          /* XK_Control_R   Right control     */
/* 0xE5 */ xx,                          /* XK_Caps_Lock   Caps lock         */
/* 0xE6 */ xx,                          /* XK_Shift_Lock  Shift lock        */
/* 0xE7 */ xx,                          /* XK_Meta_L      Left meta         */
/* 0xE8 */ xx,                          /* XK_Meta_R      Right meta        */
/* 0xE9 */ xx,                          /* XK_Alt_L       Left alt          */
/* 0xEA */ xx,                          /* XK_Alt_R       Right alt         */
/* 0xEB */ xx,                          /* XK_Super_L     Left super        */
/* 0xEC */ xx,                          /* XK_Super_R     Right super       */
/* 0xED */ xx,                          /* XK_Hyper_L     Left hyper        */
/* 0xEE */ xx,                          /* XK_Hyper_R     Right hyper       */
/* 0xEF */ xx,                          /* CF12                             */
/* 0xF0 */ p_macro31,                   /* AF1                              */
/* 0xF1 */ p_macro32,                   /* AF2                              */
/* 0xF2 */ p_macro33,                   /* AF3                              */
/* 0xF3 */ p_macro34,                   /* AF4                              */
/* 0xF4 */ p_backcolnxt,                /* AF5                              */
/* 0xF5 */ p_macro36,                   /* AF6                              */
/* 0xF6 */ p_macro37,                   /* AF7                              */
/* 0xF7 */ p_macro38,                   /* AF8                              */
/* 0xF8 */ ned_p_activate_cl_fr,        /* AF9                              */
/* 0xF9 */ p_activate_cl4,              /* AF10                             */
/* 0xFA */ xx,                          /* AF11                             */
/* 0xFB */ xx,                          /* AF12                             */
/* 0xFC */ xx,
/* 0xFD */ xx,
/* 0xFE */ xx,
/* 0xFF */ ned_del_char_right           /* XK_Delete  Delete, rubout        */

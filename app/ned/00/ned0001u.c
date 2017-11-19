/*
 *  FILE %ned/00/ned0001u.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  prefix-group u: special functions
 *
 *  written:       1992 01 19
 *  latest update: 2001-02-11 12:39:50
 *  $Id: ned0001u.c,v 1.6 2005/04/01 16:46:20 gonter Exp $
 *
 */

/* x. Praefix Ctrl U: special functions - - - - - - - - - - - - - - - - - - */
/* 00 */ xx,                    /* ^U NULL                                  */
/* 01 */ ned_show_author,       /* ^U^A: Author ausgeben                    */
/* 02 */ xx,                    /* ^U^B                                     */
/* 03 */ p_cross_ref,           /* ^U^C: Cross Referencing                  */
/* 04 */ p_mac_define,          /* ^U^D: Define Macro                       */
/* 05 */ p_edsetup,             /* ^U^E: Edit Setup file                    */
/* 06 */ p_feature_set,         /* ^U^F: Feature setzen                     */
/* 07 */ p_feature_reset,       /* ^U^G: Feature loeschen                   */
/* 08 */ ned_set_hyx_l,         /* ^U^H: hyx_l setzen                       */
/* 09 */ ned_line_end_MSDOS,    /* ^U^I: -> MSDOS Line End                  */
/* 0A */ ned_set_SGML_tag,      /* ^U^J: SGML Tag setzen                    */
/* 0B */ ned_set_SGML_entity,   /* ^U^K: SGML Entity setzen                 */
/* 0C */ DOSPRIM(p_switch_line_mode),    /* ^U^L: lines ...                 */
/* 0D */ p_menue,               /* ^U^M: Menue aktivieren                   */
/* 0E */ p_feature_next,        /* ^U^N: Jump 2 Next Feature                */
/* 0F */ ned_memorize_location, /* ^U^O: store frame or file                */

/* 10 */ p_feature_prev,        /* ^U^P: Jump 2 Prev Feature                */
/* 11 */ ned_jmp_marker_1,      /* ^U^Q: jump to marker 1                   */
/* 12 */ p_rdsetup,             /* ^U^R: Setup File einlesen                */
/* 13 */ xx,                    /* ^U^S                                     */
/* 14 */ p_window_menu,         /* ^U^T: Window Menu                        */
/* 15 */ ned_line_end_UNIX,     /* ^U^U: -> UNIX Line End                   */
/* 16 */ ned_eval_block,        /* ^U^V: Ausfuehrung eines Blocks           */
/* 17 */ p_link_feature,        /* ^U^W: Feature Window oeffnen             */
/* 18 */ ned_eval_feature,      /* ^U^X: Ausfuehrung eines Features         */
/* 19 */ ned_delete_word,       /* ^U^Y: Delete Word Right                  */
/* 1A */ xx,                    /* ^U^Z:                                    */
/* 1B */ xx,                    /* ^U^[ (ESC)                               */
/* 1C */ xx,                    /* ^U^\                                     */
/* 1D */ xx,                    /* ^U^]                                     */
/* 1E */ xx,                    /* ^U^^                                     */
/* 1F */ xx,                    /* ^U^_                                     */

/* 20 */ xx,                    /* ^U (BLANK): NO-OP                        */
/* 21 */ xx,                    /* ^U!                                      */
/* 22 */ xx,                    /* ^U"                                      */
/* 23 */ p_find_matching_bracket,/*^U#                                      */
/* 24 */ xx,                    /* ^U$                                      */
/* 25 */ ned_set_mark,          /* ^U%                                      */
/* 26 */ ned_set_lookup_tag,    /* ^U&                                      */
/* 27 */ xx,                    /* ^U'                                      */
/* 28 */ p_activate_fr_help,    /* ^U(                                      */
/* 29 */ p_activate_fr_notes,   /* ^U)                                      */
/* 2A */ ned_set_lookup_tag_fr, /* ^U*                                      */
/* 2B */ p_find_lower_bracket,  /* ^U+                                      */
/* 2C */ ned_set_lookup_tag_fr2,/* ^U,                                      */
/* 2D */ p_alt_minus,           /* ^U-                                      */
/* 2E */ xx,                    /* ^U.                                      */
/* 2F */ xx,                    /* ^U/                                      */

/* 30 */ p_macro40,             /* ^U0: Macro 40 ausfuehren                 */
/* 31 */ p_macro41,             /* ^U1                                      */
/* 32 */ p_macro42,             /* ^U2                                      */
/* 33 */ p_macro43,             /* ^U3                                      */
/* 34 */ p_macro44,             /* ^U4                                      */
/* 35 */ p_macro45,             /* ^U5                                      */
/* 36 */ p_macro46,             /* ^U6                                      */
/* 37 */ p_macro47,             /* ^U7                                      */
/* 38 */ p_macro48,             /* ^U8                                      */
/* 39 */ p_macro49,             /* ^U9                                      */
/* 3A */ xx,                    /* ^U:                                      */
/* 3B */ xx,                    /* ^U;                                      */
/* 3C */ p_logic_link_prev,     /* ^U<                                      */
/* 3D */ p_activate_fr_root,    /* ^U=                                      */
/* 3E */ p_logic_link_next,     /* ^U>                                      */
/* 3F */ xx,                    /* ^U?                                      */

/* 40 */ xx,                    /* ^U@                                      */
/* 41 */ ned_show_author,       /* ^UA: Author ausgeben                     */
/* 42 */ xx,                    /* ^UB                                      */
/* 43 */ p_cross_ref,           /* ^UC: Cross Referencing                   */
/* 44 */ p_mac_define,          /* ^UD: Define Macro                        */
/* 45 */ p_edsetup,             /* ^UE: Edit Setup file                     */
/* 46 */ p_feature_set,         /* ^UF: Feature setzen                      */
/* 47 */ p_feature_reset,       /* ^UG: Feature loeschen                    */
/* 48 */ ned_set_hyx_l,         /* ^UH: hyx_l setzen                        */
/* 49 */ ned_line_end_MSDOS,    /* ^UI: -> MSDOS Line End                   */
/* 4A */ ned_set_SGML_tag,      /* ^UJ: SGML Tag setzen                     */
/* 4B */ ned_set_SGML_entity,   /* ^UK: SGML Entity setzen                  */
/* 4C */ DOSPRIM(p_switch_line_mode),   /* ^UL: lines ...                   */
/* 4D */ p_menue,               /* ^UM: Menue aktivieren                    */
/* 4E */ p_feature_next,        /* ^UN: Jump to Next Feature                */
/* 4F */ ned_memorize_location, /* ^UO: store frame or file                 */

/* 50 */ p_feature_prev,        /* ^UP: Jump to Prev Feature                */
/* 51 */ ned_jmp_marker_1,      /* ^UQ: jump to marker 1                    */
/* 52 */ p_rdsetup,             /* ^UR: Setup File einlesen                 */
/* 53 */ xx,                    /* ^US                                      */
/* 54 */ p_window_menu,         /* ^UT: Window Menu                         */
/* 55 */ ned_line_end_UNIX,     /* ^UU: -> UNIX Line End                    */
/* 56 */ ned_eval_block,        /* ^UV: Ausfuehrung eines Blocks            */
/* 57 */ p_link_feature,        /* ^UW: Feature Window oeffnen              */
/* 58 */ ned_eval_feature,      /* ^UX: Ausfuehrung eines Features          */
/* 59 */ ned_delete_word,       /* ^UY: Delete Word Right                   */
/* 5A */ xx,                    /* ^UZ:                                     */
/* 5B */ p_activate_cl1,        /* ^U[:                                     */
/* 5C */ p_find_matching_bracket,/*^U\:                                     */
/* 5D */ p_activate_cl2,        /* ^U]:                                     */
/* 5E */ p_activate_cl0,        /* ^U^                                      */
/* 5F */ ned_p_activate_cl_fr,  /* ^U_                                      */

/* 60 */ xx,                    /* ^U`                                      */
/* 61 */ ned_show_author,       /* ^Ua: Author ausgeben                     */
/* 62 */ xx,                    /* ^Ub                                      */
/* 63 */ p_cross_ref,           /* ^Uc: Cross Referencing                   */
/* 64 */ p_mac_define,          /* ^Ud: Define Macro                        */
/* 65 */ p_edsetup,             /* ^Ue: Edit Setup file                     */
/* 66 */ p_feature_set,         /* ^Uf: Feature setzen                      */
/* 67 */ p_feature_reset,       /* ^Ug: Feature loeschen                    */
/* 68 */ ned_set_hyx_l,         /* ^Uh: hyx_l setzen                        */
/* 69 */ ned_line_end_MSDOS,    /* ^Ui: -> MSDOS Line End                   */
/* 6A */ ned_set_SGML_tag,      /* ^Uj: SGML Tag setzen                     */
/* 6B */ ned_set_SGML_entity,   /* ^Uk: SGML Entity setzen                  */
/* 6C */ DOSPRIM(p_switch_line_mode),   /* ^Ul: lines ...                   */
/* 6D */ p_menue,               /* ^Um: Menue aktivieren                    */
/* 6E */ p_feature_next,        /* ^Un: Jump 2 Next Feature                 */
/* 6F */ ned_memorize_location, /* ^Uo: store frame or file                 */

/* 70 */ p_feature_prev,        /* ^Up: Jump 2 Prev Feature                 */
/* 71 */ ned_jmp_marker_1,      /* ^U^Q: jump to marker 1                   */
/* 72 */ p_rdsetup,             /* ^Ur: Setup File einlesen                 */
/* 73 */ xx,                    /* ^Us                                      */
/* 74 */ p_window_menu,         /* ^Ut: Window Menu                         */
/* 75 */ ned_line_end_UNIX,     /* ^Uu: -> UNIX Line End                    */
/* 76 */ ned_eval_block,        /* ^Uv: Ausfuehrung eines Blocks            */
/* 77 */ p_link_feature,        /* ^Uw: Feature Window oeffnen              */
/* 78 */ ned_eval_feature,      /* ^Ux: Ausfuehrung eines Features          */
/* 79 */ ned_delete_word,       /* ^Uy: Delete Word Right                   */
/* 7A */ xx,                    /* ^Uz:                                     */
/* 7B */ p_activate_cl3,        /* ^U{                                      */
/* 7C */ xx,                    /* ^U|                                      */
/* 7D */ p_activate_cl4,        /* ^U}                                      */
/* 7E */ xx,                    /* ^U~                                      */
/* 7F */ xx                     /* ^U                                       */

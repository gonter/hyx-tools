/*
 *  FILE %ned/00/ned0001q.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe q: ^Q
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include Files fuer
 *                             jede Praefix-Gruppe
 *                 1992 01 19: alternative Hypertext Navigation
 *  latest update: 1998-07-19 21:08:26
 *  $Id: ned0001q.c,v 1.2 2005/04/01 16:46:20 gonter Exp $
 *
 */

/* 1. Praefix Ctrl Q: Quick Menue - - - - - - - - - - - - - - - - - - - - - */
/* 00 */ xx,                    /*                                          */
/* 01 */ p_replace,             /* ^Q^A: Replace                            */
/* 02 */ p_jmp_blkbeg,          /* ^Q^B: Block Beginn anspringen            */
/* 03 */ pq_dn,                 /* ^Q^C: An das Ende des Files              */
/* 04 */ ned_jmp_eoln,          /* ^Q^D: An das Ende der Zeile              */
/* 05 */ ned_vi_cursor_top,     /* ^Q^E:                                    */
/* 06 */ p_find,                /* ^Q^F: Find String                        */
/* 07 */ ned_ws_aw_find_str,    /* ^Q^G                                     */
/* 08 */ ned_ws_aw_find_str,    /* ^Q^H                                     */
/* 09 */ p_activate_cl3,        /* ^Q^I: special cluster 3                  */
/* 0A */ ned_lookup_thesaurus,  /* ^Q^J:                                    */
/* 0B */ p_jmp_blkend,          /* ^Q^K: Block Ende anspringen              */
/* 0C */ ned_lookup_lexicon,    /* ^Q^L:                                    */
/* 0D */ p_dump_macro,          /* ^Q^M: Makros ausdumpen                   */
/* 0E */ p_activate_cl2,        /* ^Q^N: special cluster 2 (notes)          */
/* 0F */ ned_p_activate_cl_fr,  /* ^Q^O: prompt for cluster and frame       */

/* 10 */ p_pfile,               /* ^Q^P: print file                         */
/* 11 */ xx,                    /* ^Q^Q                                     */
/* 12 */ pq_up,                 /* ^Q^R: An den Anfang des Files            */
/* 13 */ ned_jmp_boln,          /* ^Q^S: An den Anfang der Zeile (S!)       */
/* 14 */ xx,                    /* ^Q^T                                     */
/* 15 */ p_activate_fr_root,    /* ^Q^U: root frame in local cluster        */
/* 16 */ ned_jmp_marker_find,   /* ^Q^V: follow logic link 'menu'           */
/* 17 */ ned_jmp_aktline_top,   /* ^Q^W                                     */
/* 18 */ ned_vi_cursor_bot,     /* ^Q^X:                                    */
/* 19 */ ned_del2eoln,          /* ^Q^Y: Zeilenrest loeschen                */
/* 1A */ ned_jmp_aktline_bot,   /* ^Q^Z                                     */
/* 1B */ xx,                    /* ^Q^                                      */
/* 1C */ xx,                    /* ^Q^                                      */
/* 1D */ xx,                    /* ^Q^                                      */
/* 1E */ xx,                    /* ^Q^                                      */
/* 1F */ xx,                    /* ^Q^                                      */

/* 20 */ xx,                    /* ^Q-Blank                                 */
/* 21 */ p_shell,               /* ^Q!                                      */
/* 22 */ xx,                    /* ^Q"                                      */
/* 23 */ xx,                    /* ^Q#                                      */
/* 24 */ xx,                    /* ^Q$                                      */
/* 25 */ xx,                    /* ^Q%                                      */
/* 26 */ xx,                    /* ^Q&                                      */
/* 27 */ p_logic_link_lang,     /* ^Q': follow logic link 'lang'            */
/* 28 */ xx,                    /* ^Q(                                      */
/* 29 */ xx,                    /* ^Q)                                      */
/* 2A */ p_logic_link_more,     /* ^Q*: select from all logic links         */
/* 2B */ xx,                    /* ^Q+                                      */
/* 2C */ xx,                    /* ^Q,                                      */
/* 2D */ xx,                    /* ^Q-                                      */
/* 2E */ xx,                    /* ^Q.                                      */
/* 2F */ p_activate_fr_notes,   /* ^Q/: notes frame in local cluster        */

/* 30 */ ned_jmp_marker_key,    /* ^Q0:  Marker 0 anpringen                 */
/* 31 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 32 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 33 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 34 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 35 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 36 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 37 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 38 */ ned_jmp_marker_key,    /* ^Q                                       */
/* 39 */ ned_jmp_marker_key,    /* ^Q9                                      */
/* 3A */ xx,                    /* ^Q:                                      */
/* 3B */ xx,                    /* ^Q;                                      */
/* 3C */ p_logic_link_prev,     /* ^Q<: follow logic link 'prev'            */
/* 3D */ xx,                    /* ^Q=                                      */
/* 3E */ p_logic_link_next,     /* ^Q>: follow logic link 'next'            */
/* 3F */ p_activate_fr_help,    /* ^Q?: help frame in local cluster         */

/* 40 */ xx,                    /* ^Q@                                      */
/* 41 */ p_replace,             /* ^QA                                      */
/* 42 */ p_jmp_blkbeg,          /* ^QB: Block Beginn anspringen             */
/* 43 */ pq_dn,                 /* ^QC                                      */
/* 44 */ ned_jmp_eoln,          /* ^QD                                      */
/* 45 */ ned_vi_cursor_top,     /* ^QE:                                     */
/* 46 */ p_find,                /* ^QF                                      */
/* 47 */ ned_ws_aw_find_str,    /* ^QG                                      */
/* 48 */ ned_ws_aw_find_str,    /* ^QH                                      */
/* 49 */ p_activate_cl3,        /* ^QI: special cluster 3                   */
/* 4A */ ned_lookup_thesaurus,  /* ^QJ                                      */
/* 4B */ p_jmp_blkend,          /* ^QK: Block Ende anspringen               */
/* 4C */ ned_lookup_lexicon,    /* ^QL:                                     */
/* 4D */ xx,                    /* ^QM                                      */
/* 4E */ p_activate_cl2,        /* ^QN: special cluster 2 (notes)           */
/* 4F */ ned_p_activate_cl_fr,  /* ^QO: prompt for cluster and frame        */

/* 50 */ p_pfile,               /* ^QP: print file                          */
/* 51 */ xx,                    /* ^QQ                                      */
/* 52 */ pq_up,                 /* ^QR                                      */
/* 53 */ ned_jmp_boln,          /* ^QS                                      */
/* 54 */ xx,                    /* ^QT                                      */
/* 55 */ p_activate_fr_root,    /* ^QU: root frame in local cluster         */
/* 56 */ ned_jmp_marker_find,   /* ^QV: follow logic link 'menu'            */
/* 57 */ ned_jmp_aktline_top,   /* ^QW                                      */
/* 58 */ ned_vi_cursor_bot,     /* ^QX                                      */
/* 59 */ ned_del2eoln,          /* ^QY                                      */
/* 5A */ ned_jmp_aktline_bot,   /* ^QZ                                      */
/* 5B */ ned_jmp_marker_key,    /* ^Q[                                      */
/* 5C */ xx,                    /* ^Q\                                      */
/* 5D */ ned_jmp_marker_key,    /* ^Q]                                      */
/* 5E */ p_logic_link_up,       /* ^Q^: follow logic link 'up'              */
/* 5F */ xx,                    /* ^Q_                                      */

/* 60 */ p_close_jou,           /* ^Q`: Jour File schliessen                */
/* 61 */ p_replace,             /* ^Qa                                      */
/* 62 */ p_jmp_blkbeg,          /* ^Qb: Block Beginn anspringen             */
/* 63 */ pq_dn,                 /* ^Qc                                      */
/* 64 */ ned_jmp_eoln,          /* ^Qd                                      */
/* 65 */ ned_vi_cursor_top,     /* ^Qe:                                     */
/* 66 */ p_find,                /* ^Qf                                      */
/* 67 */ ned_ws_aw_find_str,    /* ^Qg                                      */
/* 68 */ ned_ws_aw_find_str,    /* ^Qh                                      */
/* 69 */ p_activate_cl3,        /* ^Qi: special cluster 3                   */
/* 6A */ ned_lookup_thesaurus,  /* ^Qj                                      */
/* 6B */ p_jmp_blkend,          /* ^Qk: Block Ende anspringen               */
/* 6C */ ned_lookup_lexicon,    /* ^Ql:                                     */
/* 6D */ xx,                    /* ^Qm                                      */
/* 6E */ p_activate_cl2,        /* ^Qn: special cluster 2 (notes)           */
/* 6F */ ned_p_activate_cl_fr,  /* ^Qo: prompt for cluster and frame        */

/* 70 */ p_pfile,               /* ^Qp: print file                          */
/* 71 */ xx,                    /* ^Qq                                      */
/* 72 */ pq_up,                 /* ^Qr                                      */
/* 73 */ ned_jmp_boln,          /* ^Qs                                      */
/* 74 */ xx,                    /* ^Qt                                      */
/* 75 */ p_activate_fr_root,    /* ^Qu: root frame in local cluster         */
/* 76 */ ned_jmp_marker_find,   /* ^Qv: follow logic link 'menu'            */
/* 77 */ ned_jmp_aktline_top,   /* ^Qw                                      */
/* 78 */ ned_vi_cursor_bot,     /* ^Qx                                      */
/* 79 */ ned_del2eoln,          /* ^Qy                                      */
/* 7A */ ned_jmp_aktline_bot,   /* ^Qz                                      */
/* 7B */ xx,                    /* ^Q{                                      */
/* 7C */ xx,                    /* ^Q|                                      */
/* 7D */ xx,                    /* ^Q}                                      */
/* 7E */ xx,                    /* ^Q~                                      */
/* 7F */ xx                     /* ^Q                                       */

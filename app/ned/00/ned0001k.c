/*
 *  FILE %ned/00/ned0001k.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe k: ^K
 *  see also: ned0001.c
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1992 01 16: Aufteilung in include files fuer
 *                             jede Praefix-Gruppe
 *                 1993-08-29
 *  latest update: 2000-08-11  6:55:27
 *  $Id: ned0001k.c,v 1.3 2001/02/12 00:03:14 gonter Exp $
 *
 */

/* 2. Praefix Ctrl K: Block and File Operations - - - - - - - - - - - - - - */
/* 00 */ xx,
/* 01 */ ned_blk_append,        /* ^K^A: Block Append to File               */
/* 02 */ p_blkbeg,              /* ^K^B: Block Begin Marker setzen          */
/* 03 */ ned_blk_copy,          /* ^K^C: Block Copy                         */
/* 04 */ p_ssave,               /* ^K^D: Save File and Close Window         */
/* 05 */ ned_eval_str,          /* ^K^E: eval string                        */
/* 06 */ p_show_tag,            /* ^K^F: reload but show tags as text       */
/* 07 */ p_fget,                /* ^K^G: Lese File ein                      */
/* 08 */ p_hideblk,             /* ^K^H: Block Hide Toggle                  */
/* 09 */ ned_blk_iconify,       /* ^K^I: iconify block                      */
/* 0A */ xx,                    /* ^K^J                                     */
/* 0B */ p_blkend,              /* ^K^K: Block End Marker setzen            */
/* 0C */ p_link,                /* ^K^L: Window auf File verketten          */
/* 0D */ xx,                    /* ^K^M                                     */
/* 0E */ ned_rename_object,     /* ^K^N: File umbenennen                    */
/* 0F */ xx,                    /* ^K^O                                     */

/* 10 */ ned_blk_print,         /* ^K^P: print block                        */
/* 11 */ p_abandon,             /* ^K^Q: File verwerfen                     */
/* 12 */ ned_blk_read,          /* ^K^R: Read Block from File               */
/* 13 */ p_save,                /* ^K^S: Save File                          */
/* 14 */ ned_pico_exit,         /* ^K^T: Save As ...                        */
/* 15 */ p_unlink,              /* ^K^U  unlink a window from window chain  */
/* 16 */ ned_blk_move,          /* ^K^V: Block verschieben                  */
/* 17 */ ned_blk_write,         /* ^K^W: Write Block to File                */
/* 18 */ p_sx,                  /* ^K^X: Alle Files sichern und AUS         */
/* 19 */ ned_blk_delete,        /* ^K^Y: Block loeschen                     */
/* 1A */ p_qabandon,            /* ^K^Z: Editieren abbrechen                */
/* 1B */ xx,                    /* ^K^                                      */
/* 1C */ xx,                    /* ^K^                                      */
/* 1D */ xx,                    /* ^K^                                      */
/* 1E */ xx,                    /* ^K^                                      */
/* 1F */ xx,                    /* ^K^                                      */

/* 20 */ xx,                    /* ^K-Blank: Reset Prefix                   */
/* 21 */ ned_paste_file_name,   /* ^K!                                      */
/* 22 */ ned_paste_user,        /* ^K": for german keyboards                */
/* 23 */ ned_paste_date,        /* ^K#                                      */
/* 24 */ ned_paste_date_time,   /* ^K$                                      */
/* 25 */ ned_group_set_marker,  /* ^K%                                      */
/* 26 */ ned_paste_date_string, /* ^K&                                      */
/* 27 */ xx,                    /* ^K'                                      */
/* 28 */ ned_set_marker_key,    /* ^K(                                      */
/* 29 */ ned_set_marker_key,    /* ^K)                                      */
/* 2A */ ned_paste_seconds,     /* ^K*                                      */
/* 2B */ ned_blk_mode,          /* ^K+: Block Mode aendern                  */
/* 2C */ xx,                    /* ^K,                                      */
/* 2D */ xx,                    /* ^K-:                                     */
/* 2E */ xx,                    /* ^K.                                      */
/* 2F */ p_extract,             /* ^K/: extract current information         */

/* 30 */ ned_set_marker_key,    /* ^K0: Marker 0 setzen                     */
/* 31 */ ned_set_marker_key,    /* ^K1                                      */
/* 32 */ ned_set_marker_key,    /* ^K2                                      */
/* 33 */ ned_set_marker_key,    /* ^K3                                      */
/* 34 */ ned_set_marker_key,    /* ^K4                                      */
/* 35 */ ned_set_marker_key,    /* ^K5                                      */
/* 36 */ ned_set_marker_key,    /* ^K6                                      */
/* 37 */ ned_set_marker_key,    /* ^K7                                      */
/* 38 */ ned_set_marker_key,    /* ^K8                                      */
/* 39 */ ned_set_marker_key,    /* ^K9                                      */
/* 3A */ xx,                    /* ^K:                                      */
/* 3B */ xx,                    /* ^K;                                      */
/* 3C */ TK(ned_tk_import_selection),  /*^K< import current selection       */
/* 3D */ xx,                    /* ^K=                                      */
/* 3E */ TK(ned_tk_claim_selection),/* ^K>                                  */
/* 3F */ ned_paste_renamed_object, /* ^K?                                   */

/* 40 */ ned_paste_user,        /* ^K@                                      */
/* 41 */ ned_blk_append,        /* ^KA                                      */
/* 42 */ p_blkbeg,              /* ^KB                                      */
/* 43 */ ned_blk_copy,          /* ^KC                                      */
/* 44 */ p_ssave,               /* ^KD                                      */
/* 45 */ ned_eval_str,          /* ^KE                                      */
/* 46 */ p_show_tag_normally,   /* ^KF: reload but show tags normally       */
/* 47 */ p_fget,                /* ^KG                                      */
/* 48 */ p_hideblk,             /* ^KH                                      */
/* 49 */ ned_blk_iconify,       /* ^KI: iconify block                       */
/* 4A */ xx,                    /* ^KJ                                      */
/* 4B */ p_blkend,              /* ^KK                                      */
/* 4C */ p_link,                /* ^KL                                      */
/* 4D */ xx,                    /* ^KM                                      */
/* 4E */ ned_rename_object,     /* ^KN                                      */
/* 4F */ xx,                    /* ^KO                                      */

/* 50 */ ned_blk_print,         /* ^KP: print block                         */
/* 51 */ p_abandon,             /* ^KQ                                      */
/* 52 */ ned_blk_read,          /* ^KR                                      */
/* 53 */ p_save,                /* ^KS                                      */
/* 54 */ ned_pico_exit,         /* ^KT                                      */
/* 55 */ p_unlink,              /* ^KU                                      */
/* 56 */ ned_blk_move,          /* ^KV                                      */
/* 57 */ ned_blk_write,         /* ^KW                                      */
/* 58 */ p_sx,                  /* ^KX                                      */
/* 59 */ ned_blk_delete,        /* ^KY                                      */
/* 5A */ p_qabandon,            /* ^KZ                                      */
/* 5B */ ned_set_marker_key,    /* ^K[                                      */
/* 5C */ ned_group_set_marker,  /* ^K\                                      */
/* 5D */ ned_set_marker_key,    /* ^K]                                      */
/* 5E */ xx,                    /* ^K^                                      */
/* 5F */ xx,                    /* ^K_                                      */

/* 60 */ xx,                    /* ^K`                                      */
/* 61 */ ned_blk_append,        /* ^Ka                                      */
/* 62 */ p_blkbeg,              /* ^Kb                                      */
/* 63 */ ned_blk_copy,          /* ^Kc                                      */
/* 64 */ p_ssave,               /* ^Kd                                      */
/* 65 */ ned_eval_str,          /* ^Ke                                      */
/* 66 */ p_save_reload,         /* ^Kf: reload text; see also ^K^F, ^KF     */
/* 67 */ p_fget,                /* ^Kg                                      */
/* 68 */ p_hideblk,             /* ^Kh                                      */
/* 69 */ ned_blk_iconify,       /* ^Ki: iconify block                       */
/* 6A */ xx,                    /* ^Kj                                      */
/* 6B */ p_blkend,              /* ^Kk                                      */
/* 6C */ p_link,                /* ^Kl                                      */
/* 6D */ xx,                    /* ^Km                                      */
/* 6E */ ned_rename_object,     /* ^Kn                                      */
/* 6F */ xx,                    /* ^Ko                                      */

/* 70 */ ned_blk_print,         /* ^Kp: print block                         */
/* 71 */ p_abandon,             /* ^Kq                                      */
/* 72 */ ned_blk_read,          /* ^Kr                                      */
/* 73 */ p_save,                /* ^Ks                                      */
/* 74 */ ned_pico_exit,         /* ^Kt                                      */
/* 75 */ p_unlink,              /* ^Ku                                      */
/* 76 */ ned_blk_move,          /* ^Kv                                      */
/* 77 */ ned_blk_write,         /* ^Kw                                      */
/* 78 */ p_sx,                  /* ^Kx                                      */
/* 79 */ ned_blk_delete,        /* ^Ky                                      */
/* 7A */ p_qabandon,            /* ^Kz                                      */
/* 7B */ ned_set_marker_key,    /* ^K{                                      */
/* 7C */ xx,                    /* ^K|                                      */
/* 7D */ ned_set_marker_key,    /* ^K}                                      */
/* 7E */ xx,                    /* ^K~                                      */
/* 7F */ xx                     /* ^K-Delete                                */

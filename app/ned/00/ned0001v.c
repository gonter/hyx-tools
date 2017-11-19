/*
 *  FILE %ned/00/ned0001v.c
 *
 *  jumptable for editor NED: vi jump table
 *  included by ned0001.c
 *
 *  written:       1993-07-31
 *  latest update: 1997-09-07 13:31:47
 *  $Id: ned0001v.c,v 1.5 2007/12/02 11:55:23 gonter Exp $
 *
 */

/* vi jump table  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* 00 */ xx,                    /*                                          */
/* 01 */ p_ctrlu,               /* ^A: command_table_U     UNUSED IN VI     */
/* 02 */ ned_page_up,           /* ^B: page up                              */
/* 03 */ xx,                    /* ^C:                     UNUSED IN VI     */
/* 04 */ ned_half_page_down,    /* ^D: (half) page down                     */
/* 05 */ p_upscr,               /* ^E:                                      */
/* 06 */ ned_page_down,         /* ^F: page down                            */
/* 07 */ ned_line_info,         /* ^G:                                      */
/* 08 */ ned_cursor_left,       /* ^H: cursor left                          */
/* 09 */ xx,                    /* ^I:                     UNUSED IN VI     */
/* 0A */ ned_cursor_down,       /* ^J:                                      */
/* 0B */ p_ctrlk,               /* ^K: command_table_K;    UNUSED IN VI !!! */
/* 0C */ p_refresh,             /* ^L: redraw current window                */
/* 0D */ ned_cursor_down,       /* ^M: cursor down                          */
/* 0E */ xx,                    /* ^N:                                      */
/* 0F */ p_ctrlo,               /* ^O: command_table_O;    UNUSED IN VI !!! */

/* 10 */ ned_cursor_up,         /* ^P:                                      */
/* 11 */ p_ctrlq,               /* ^Q: commant_table_Q:    UNUSED IN VI !!! */
/* 12 */ p_refresh,             /* ^R:                                      */
/* 13 */ xx,                    /* ^S                      UNUSED IN VI     */
/* 14 */ xx,                    /* ^T:                     UNUSED IN VI     */
/* 15 */ ned_half_page_up,      /* ^U: (half) page up                       */
/* 16 */ ned_ctrlp,             /* ^V: insert literal next;NVI Extension    */
/* 17 */ vi_dkey,               /* ^W: VIM extensions      UNUSED IN VI !!! */
/* 18 */ p_ctrlu,               /* ^X: Command Table U     UNUSED IN VI     */
/* 19 */ p_dnscr,               /* ^Y:                                      */
/* 1A */ xx,                    /* ^Z:                                      */
/* 1B */ vi_bell,               /* ^[: ESC                                  */
/* 1C */ p_ctrlu,               /* ^\:                                      */
/* 1D */ q_eval_tag,            /* ^]: interpret token as tag and go there  */
/* 1E */ xx,                    /* ^                                        */
/* 1F */ xx,                    /* ^                                        */

/* 20 */ ned_cursor_right,              /* SPACE: cursor right                      */
/* 21 */ xx,                    /*                                          */
/* 22 */ xx,                    /*                                          */
/* 23 */ xx,                    /*                                          */
/* 24 */ ned_jmp_eoln,          /* $: to end of line                        */
/* 25 */ p_find_matching_bracket,/*%:                                       */
/* 26 */ xx,                    /*                                          */
/* 27 */ vi_dkey,               /* ': jump to begin of line with marker     */
/* 28 */ xx,                    /*                                          */
/* 29 */ xx,                    /*                                          */
/* 2A */ xx,                    /* *                          UNUSED IN VI  */
/* 2B */ vi_jmp_next_boln,      /* +                                        */
/* 2C */ ned_vi_find_next_rev,  /* ,: find next character, reverse direction*/
/* 2D */ vi_jmp_prev_boln,      /* -                                        */
/* 2E */ vi_repeat_last_command,/* .: repeat last command                   */
/* 2F */ vi_find_forward,       /* /: find something                        */

/* 30 */ vi_digit,              /* 0:                                       */
/* 31 */ vi_digit,              /* 1                                        */
/* 32 */ vi_digit,              /* 2                                        */
/* 33 */ vi_digit,              /* 3                                        */
/* 34 */ vi_digit,              /* 4                                        */
/* 35 */ vi_digit,              /* 5                                        */
/* 36 */ vi_digit,              /* 6                                        */
/* 37 */ vi_digit,              /* 7                                        */
/* 38 */ vi_digit,              /* 8                                        */
/* 39 */ vi_digit,              /* 9                                        */
/* 3A */ vi_ex,                 /* :: ex command line mode                  */
/* 3B */ ned_vi_find_next,      /* ;                                        */
/* 3C */ xx,                    /* <                                        */
/* 3D */ xx,                    /* =                         UNUSED IN VI   */
/* 3E */ xx,                    /* >                                        */
/* 3F */ vi_find_backward,      /* ?                                        */

/* 40 */ xx,                    /* @:                                       */
/* 41 */ vi_append_eol,         /* A:                                       */
/* 42 */ p_word_left_2,         /* B: move character right, ingnore punct.  */
/* 43 */ vi_change_2eoln,       /* C: replace text until EOLN               */
/* 44 */ ned_del2eoln,          /* D: delete rest of line                   */
/* 45 */ p_word_right_end_2,    /* E:                                       */
/* 46 */ vi_dkey,               /* F:                                       */
/* 47 */ vi_jmp_2line,          /* G: goto specified or line in file        */
/* 48 */ ned_vi_cursor_top,     /* H: move cursor to top of the screen      */
/* 49 */ vi_insert_bol,         /* I:                                       */
/* 4A */ vi_join,               /* J: join line                             */
/* 4B */ xx,                    /* K:                         UNUSED IN VI  */
/* 4C */ ned_vi_cursor_bot,     /* L: move cursor to bottom of the screen   */
/* 4D */ ned_vi_cursor_mid,     /* M: move cursor to mid screen             */
/* 4E */ xx,                    /* N:                                       */
/* 4F */ vi_insert_before_line, /* O:                                       */

/* 50 */ ned_buffer_copy_before,/* P:                                       */
/* 51 */ xx,                    /* Q:                                       */
/* 52 */ vi_ovr,                /* R: overwrite mode                        */
/* 53 */ vi_change_line,        /* S: delete current line and insert new 1  */
/* 54 */ vi_dkey,               /* T:                                       */
/* 55 */ xx,                    /* U:                                       */
/* 56 */ xx,                    /* V:                        UNUSED IN VI   */
/* 57 */ p_word_right_beg_2,    /* W: move curse left one word              */
/* 58 */ ned_del_char_left,     /* X: delete character left                 */
/* 59 */ vi_yank,               /* Y:                                       */
/* 5A */ vi_dkey,               /* Z:                                       */
/* 5B */ xx,                    /* [:                                       */
/* 5C */ xx,                    /* \:                        UNUSED IN VI   */
/* 5D */ xx,                    /* ]:                                       */
/* 5E */ vi_jmp_boln,           /* ^: to begin of line                      */
/* 5F */ vi_jmp_boln,           /* _: nvi: bold of cnt-1 line down,         */
                                /*                           UNUSED IN VI   */

/* 60 */ vi_dkey,               /* `: jump to named marker                  */
/* 61 */ vi_append,             /* a:                                       */
/* 62 */ p_word_left,           /* b: word left                             */
/* 63 */ vi_dkey,               /* c: double: change word                   */
/* 64 */ vi_dkey,               /* d: double: delete line                   */
/* 65 */ p_word_right_end,      /* e: move cursor right to end of word      */
/* 66 */ vi_dkey,               /* f:                                       */
/* 67 */ xx,                    /* g:                        UNUSED IN VI   */
/* 68 */ ned_cursor_left,       /* h: cursor left                           */
/* 69 */ vi_ins,                /* i: insert mode                           */
/* 6A */ ned_cursor_down,       /* j: cursor down                           */
/* 6B */ ned_cursor_up,         /* k: cursor up                             */
/* 6C */ ned_cursor_right,      /* l: cursor right                          */
/* 6D */ vi_dkey,               /* m: set named marker                      */
/* 6E */ p_fr_next,             /* n: find next item                        */
/* 6F */ vi_insert_after_line,  /* o:                                       */

/* 70 */ ned_buffer_copy,       /* p: put, here it is copy block            */
/* 71 */ xx,                    /* q:                        UNUSED IN VI   */
/* 72 */ vi_dkey,               /* r: double: replace one character         */
/* 73 */ vi_substitute,         /* s: substitute character on cursor pos.   */
/* 74 */ vi_dkey,               /* t:                                       */
/* 75 */ xx,                    /* u:                                       */
/* 76 */ xx,                    /* v:                        UNUSED IN VI   */
/* 77 */ p_word_right_beg,      /* w: move cursor right to begin of word    */
/* 78 */ ned_del_char_right,    /* x: delete character right                */
/* 79 */ vi_dkey,               /* y: double key: yank                      */
/* 7A */ vi_dkey,               /* z: redraw and position cursor            */
/* 7B */ xx,                    /* {:                                       */
/* 7C */ vi_jmp_column,         /* |:                                       */
/* 7D */ xx,                    /* }:                                       */
/* 7E */ p_toggle_case,         /* ~: toggle character cases                */
/* 7F */ ned_cursor_left        /* DEL                                      */

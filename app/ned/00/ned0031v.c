/*
 *  FILE %ned/00/ned0031v.c
 *
 *  jumptable for editor NED: vi jump table
 *
 *  written:       1993-07-31
 *                 1994-10-16: cloned from ned0001v.c
 *  latest update: 1997-08-03  9:41:49
 *
 */

/* vi jump table  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* 00 */ xx,                    /*                                          */
/* 01 */ xx,                    /* ^A:                                      */
/* 02 */ ned_page_up,           /* ^B: page up                              */
/* 03 */ xx,                    /* ^C:                                      */
/* 04 */ ned_half_page_down,    /* ^D: (half) page down                     */
/* 05 */ p_upscr,               /* ^E:                                      */
/* 06 */ ned_page_down,         /* ^F: page down                            */
/* 07 */ xx,                    /* ^G:                                      */
/* 08 */ ned_cursor_left,               /* ^H: cursor left                          */
/* 09 */ xx,                    /* ^I:                                      */
/* 0A */ ned_cursor_down,       /* ^J:                                      */
/* 0B */ xx,                    /* ^K:                                      */
/* 0C */ p_refresh,             /* ^L: redraw current window                */
/* 0D */ ned_cursor_down,       /* ^M: cursor down                          */
/* 0E */ xx,                    /* ^N:                                      */
/* 0F */ xx,                    /* ^O:                                      */

/* 10 */ ned_cursor_up,         /* ^P:                                      */
/* 11 */ xx,                    /* ^Q                                       */
/* 12 */ p_refresh,             /* ^R:                                      */
/* 13 */ xx,                    /* ^S                                       */
/* 14 */ xx,                    /* ^T:                                      */
/* 15 */ ned_half_page_up,      /* ^U: (half) page up                       */
/* 16 */ xx,                    /* ^V:                                      */
/* 17 */ xx,                    /* ^W:                                      */
/* 18 */ xx,                    /* ^X:                                      */
/* 19 */ p_dnscr,               /* ^Y:                                      */
/* 1A */ xx,                    /* ^Z:                                      */
/* 1B */ vi_bell,               /* ESC:                                     */
/* 1C */ xx,                    /* ^                                        */
/* 1D */ xx,                    /* ^                                        */
/* 1E */ xx,                    /* ^                                        */
/* 1F */ xx,                    /* ^                                        */

/* 20 */ ned_cursor_right,              /* SPACE: cursor right                      */
/* 21 */ xx,                    /*                                          */
/* 22 */ xx,                    /*                                          */
/* 23 */ xx,                    /*                                          */
/* 24 */ ned_jmp_eoln,          /* $: to end of line                        */
/* 25 */ p_find_matching_bracket,/*%:                                       */
/* 26 */ xx,                    /*                                          */
/* 27 */ xx,                    /*                                          */
/* 28 */ xx,                    /*                                          */
/* 29 */ xx,                    /*                                          */
/* 2A */ xx,                    /* *                                        */
/* 2B */ ned_cursor_down,       /* +                                        */
/* 2C */ xx,                    /*                                          */
/* 2D */ ned_cursor_up,         /* -                                        */
/* 2E */ xx /* vi_repeat_last_command */, /* .: repeat last command         */
/* 2F */ p_find,                /* /: find something                        */

/* 30 */ xx,                    /* 0:                                       */
/* 31 */ xx,                    /* 1                                        */
/* 32 */ xx,                    /* 2                                        */
/* 33 */ xx,                    /* 3                                        */
/* 34 */ xx,                    /* 4                                        */
/* 35 */ xx,                    /* 5                                        */
/* 36 */ xx,                    /* 6                                        */
/* 37 */ xx,                    /* 7                                        */
/* 38 */ xx,                    /* 8                                        */
/* 39 */ xx,                    /* 9                                        */
/* 3A */ xx /* vi_ex */,        /* :: ex command line mode                  */
/* 3B */ xx,                    /*                                          */
/* 3C */ xx,                    /*                                          */
/* 3D */ xx,                    /* =                                        */
/* 3E */ xx,                    /*                                          */
/* 3F */ xx,                    /*                                          */

/* 40 */ xx,                    /*                                          */
/* 41 */ xx,                    /* A:                                       */
/* 42 */ p_word_left,           /* B: wie W und b                           */
/* 43 */ xx,                    /* C:                                       */
/* 44 */ xx,                    /* D: delete rest of line                   */
/* 45 */ xx,                    /* E:                                       */
/* 46 */ xx,                    /* F:                                       */
/* 47 */ ned_pr_jump_to_line,   /* G: goto specified line number            */
/* 48 */ xx,                    /* H:                                       */
/* 49 */ xx,                    /* I:                                       */
/* 4A */ xx,                    /* J: join line                             */
/* 4B */ xx,                    /* K:                                       */
/* 4C */ xx,                    /* L:                                       */
/* 4D */ xx,                    /* M:                                       */
/* 4E */ xx,                    /* N:                                       */
/* 4F */ xx,                    /* O:                                       */

/* 50 */ xx,                    /* P:                                       */
/* 51 */ xx,                    /* Q                                        */
/* 52 */ xx,                    /* R: overwrite mode                        */
/* 53 */ xx,                    /* S                                        */
/* 54 */ xx,                    /* T:                                       */
/* 55 */ xx,                    /* U:                                       */
/* 56 */ xx,                    /* V:                                       */
/* 57 */ p_word_left,           /* W: move curse left one word              */
/* 58 */ xx,                    /* X: delete character left                 */
/* 59 */ xx,                    /* Y:                                       */
/* 5A */ vi_dkey,               /* Z:                                       */
/* 5B */ xx,                    /* [:                                       */
/* 5C */ xx,                    /* \:                                       */
/* 5D */ xx,                    /* ]:                                       */
/* 5E */ ned_jmp_boln,          /* ^: to begin of line                      */
/* 5F */ xx,                    /* _                                        */

/* 60 */ xx,                    /*                                          */
/* 61 */ vi_append,             /* a:                                       */
/* 62 */ p_word_left,           /* b: word left                             */
/* 63 */ xx,                    /* c: double: change word                   */
/* 64 */ xx,                    /* d: double: delete line                   */
/* 65 */ p_word_right_end,      /* e: move cursor right to end of word      */
/* 66 */ xx,                    /* f:                                       */
/* 67 */ xx,                    /* g:                                       */
/* 68 */ ned_cursor_left,       /* h: cursor left                           */
/* 69 */ vi_ins,                /* i: insert mode                           */
/* 6A */ ned_cursor_down,       /* j: cursor down                           */
/* 6B */ ned_cursor_up,         /* k: cursor up                             */
/* 6C */ ned_cursor_right,      /* l: cursor right                          */
/* 6D */ xx,                    /* m:                                       */
/* 6E */ p_fr_next,             /* n: find next item                        */
/* 6F */ xx,                    /* o:                                       */

/* 70 */ xx,                    /* p: put, here it is copy block            */
/* 71 */ xx,                    /* q                                        */
/* 72 */ xx,                    /* r: double: replace one character         */
/* 73 */ xx,                    /* s                                        */
/* 74 */ xx,                    /* t:                                       */
/* 75 */ xx,                    /* u:                                       */
/* 76 */ xx,                    /* v:                                       */
/* 77 */ p_word_right_beg,      /* w: move cursor right to begin of word    */
/* 78 */ ned_del_char_right,    /* x: delete character right                */
/* 79 */ xx,                    /* y: double key: yank                      */
/* 7A */ xx,                    /* z:                                       */
/* 7B */ xx,                    /*                                          */
/* 7C */ xx,                    /*                                          */
/* 7D */ xx,                    /*                                          */
/* 7E */ xx,                    /* ~: toggle character cases                */
/* 7F */ xx                     /*                                          */

/*
 *  FILE %ned/00/ned0016p.c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  Praefix-Gruppe a (kein Praefix)/Control in PICO Mode
 *
 *  written:       1996-05-16
 *  latest update: 1999-05-01 10:39:30
 *
 */

/* 0. normale Zeichen; keine Prefix-Codes - - - - - - - - - - - - - - - - - */
/* 00 */ xx,            /* Char  0x00:   Funktionstasten-PFX bei PC         */
/* 01 */ ned_jmp_boln,  /*         ^A: * move to the beginning of the line  */
/* 02 */ ned_cursor_left,       /*         ^B: * move backward a character          */
/* 03 */ xx,            /*         ^C:                                      */
/* 04 */ ned_del_char_right,    /* ^D: * delete character at cursor pos.    */
/* 05 */ ned_jmp_eoln,  /*         ^E: * move to the end of the line        */
/* 06 */ ned_cursor_right,      /*         ^F: * forward a character                */
/* 07 */ pico_help,     /*         ^G: * Get Help                           */
/* 08 */ ned_del_char_left, /* DEL ^H: * ein Zeichen links  loeschen        */
/* 09 */ tabulate,      /* TAB     ^I: * Tabulator                          */
#ifdef MSDOS
/* 0A */ p_ax_lng,      /*         ^J:   Ans Zeilenanfang/Zeilenende        */
#else
/* 0A */ p_nl,          /*         ^J:   Leerzeile und naechste Zeile       */
#endif
/* 0B */ ned_delete_line, /*       ^K:                                      */
/* 0C */ p_refresh,     /*         ^L: * refresh the display                */
/* 0D */ p_nl,          /*         ^M:   Leerzeile und naechste Zeile       */
/* 0E */ ned_cursor_down,/*        ^N: * move to the next line              */
/* 0F */ ned_rename_and_save, /*   ^O: * write out                          */

/* 10 */ ned_cursor_up, /*         ^P: * move to the previous line          */
/* 11 */ p_ctrlq,       /*         ^Q:   Subprozessor ^Q: ned0001q.c        */
/* 12 */ ned_blk_read,  /*         ^R: * Read File                          */
/* 13 */ xx,            /*         ^S:                                      */
/* 14 */ xx,            /*         ^T:                                      */
/* 15 */ ned_buffer_copy,/*        ^U:                                      */
/* 16 */ ned_page_down, /*         ^V: * Page Down                          */
/* 17 */ pico_find,     /*         ^W: * Where Is (find)                    */
/* 18 */ ned_pico_exit, /*         ^X: * Exit                               */
/* 19 */ ned_page_up,   /*         ^Y: * Page Up                            */
/* 1A */ p_replace,     /*         ^Z:   find/replace (from WordStar mode)  */
/* 1B */ vi_on,         /* ESC           see: ned0001v.c                    */
/* 1C */ ned_cursor_right,      /* CURSOR        Cursor nach rechts         */
/* 1D */ ned_cursor_left,       /* CURSOR        Cursor nach links          */
/* 1E */ ned_cursor_up,         /* CURSOR        Cursor eine Zeile hinauf   */
/* 1F */ ned_cursor_down        /* CURSOR        Cursor eine Zeile hinunter */
